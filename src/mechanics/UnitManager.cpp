/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "UnitManager.h"

#include "Building.h"
#include "Civilization.h"
#include "Missile.h"
#include "Player.h"
#include "Farm.h"
#include "UnitFactory.h"
#include "actions/ActionAttack.h"
#include "actions/ActionMove.h"
#include "audio/AudioPlayer.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "core/Utility.h"
#include "global/EventManager.h"
#include "mechanics/Player.h"
#include "render/SfmlRenderTarget.h"
#include "Map.h"

#include <genie/Types.h>
#include <genie/dat/Unit.h>
#include <genie/dat/UnitCommand.h>
#include <genie/dat/unit/Action.h>

#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <algorithm>
#include <utility>

namespace genie {
class Tech;
}  // namespace genie

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
}

void UnitManager::add(const Unit::Ptr &unit)
{
    if (IS_UNLIKELY(!unit)) {
        WARN << "trying to add null unit";
        return;
    }
    unit->setMap(m_map);
    m_units.push_back(unit);
    if (unit->hasAutoTargets()) {
        m_unitsWithActions.insert(unit);
    }

    EventManager::unitCreated(unit.get());
}

void UnitManager::remove(const Unit::Ptr &unit)
{
    // Could just mark it as dead, but don't want a corpse, I think
    if (m_selectedUnits.count(unit)) {
        EventManager::unitDeselected(unit.get());
        m_selectedUnits.erase(unit);
    }

    m_unitsWithActions.erase(unit);

    UnitVector::iterator it = std::find(m_units.begin(), m_units.end(), unit);
    if (it != m_units.end()) {
        EventManager::unitDying(unit.get()); // not sure about this, but whatever
        m_units.erase(it);
    }
    // TODO: EventManager::unitDisappeared(), we need to check the visibility maps
}

bool UnitManager::init()
{
    m_moveTargetMarker = std::make_unique<MoveTargetMarker>();
    m_moveTargetMarker->setMap(m_map);

    return true;
}

bool UnitManager::update(Time time)
{
    bool updated = false;

    if (m_unitsMoved) {
        m_unitsMoved = false;

        for (const Unit::Ptr &unit : m_unitsWithActions) {
            unit->checkForAutoTargets();
        }
    }

    // Update missiles (siege rockthings, arrows, etc.)
    std::unordered_set<Missile::Ptr>::iterator missileIterator = m_missiles.begin();
    while (missileIterator != m_missiles.end()) {
        const Missile::Ptr &missile = *missileIterator;
        updated = missile->update(time) || updated;
        if (!missile->isFlying() && !missile->isExploding()) {
            missileIterator = m_missiles.erase(missileIterator);
            updated = true;
        } else {
            missileIterator++;
        }
    }

    // Update decaying entities (smoke stuff from siege, corpses, etc.)
    std::unordered_set<DecayingEntity::Ptr>::iterator decayingEntityIterator = m_decayingEntities.begin();
    while (decayingEntityIterator != m_decayingEntities.end()) {
        const DecayingEntity::Ptr &entity = *decayingEntityIterator;
        updated = entity->update(time) || updated;
        if (!entity->decaying()) {
            decayingEntityIterator = m_decayingEntities.erase(decayingEntityIterator);
            updated = true;
        } else {
            decayingEntityIterator++;
        }
    }

    // Clean up dead units
    UnitVector::iterator unitIterator = m_units.begin();
    while (unitIterator != m_units.end()) {
        const Unit::Ptr &unit = *unitIterator;

        const bool isDead = unit->isDead();
        const bool isDying = unit->isDying();

        // Remove from selected if it is dying
        if (isDead || isDying) {
            m_selectedUnits.erase(unit);
            EventManager::unitDeselected(unit.get());
        }

        if (isDead) {
            EventManager::unitDying(unit.get());

            DecayingEntity::Ptr corpse = UnitFactory::Inst().createCorpseFor(unit);
            if (corpse) {
                m_decayingEntities.insert(corpse);
                updated = true;
            }
            m_unitsWithActions.erase(unit);

            unitIterator = m_units.erase(unitIterator);
        } else {
            unitIterator++;
        }
    }

    // Update the living units that are left
    for (const Unit::Ptr &unit : m_units) {
        updated = unit->update(time) || updated;
    }

    updated = m_moveTargetMarker->update(time) || updated;

    return updated;
}

void UnitManager::render(const std::shared_ptr<SfmlRenderTarget> &renderTarget, const std::vector<std::weak_ptr<Entity>> &visible)
{
    Player::Ptr humanPlayer = m_humanPlayer.lock();
    if (!humanPlayer) {
        WARN << "human gone!";
        return;
    }

    CameraPtr camera = renderTarget->camera();

    if (Size(m_outlineOverlay.getSize()) != renderTarget->getSize()) {
        m_outlineOverlay.create(renderTarget->getSize().width, renderTarget->getSize().height);
    }

    if (camera->targetPosition() != m_previousCameraPos || m_outlineOverlay.getSize().x == 0) {
        for (const Unit::Ptr &unit : m_units) {
            unit->isVisible = false;
        }
        for (const Missile::Ptr &missile : m_missiles) {
            missile->isVisible = false;
        }
        for (const DecayingEntity::Ptr &entity : m_decayingEntities) {
            entity->isVisible = false;
        }
        m_previousCameraPos = camera->targetPosition();
    }

    std::vector<Unit::Ptr> visibleUnits;
    std::vector<Missile::Ptr> visibleMissiles;
    for (const std::weak_ptr<Entity> &e : visible) {
        std::shared_ptr<Entity> entity = e.lock();
        if (!entity) {
            WARN << "got dead entity";
            continue;
        }

        const VisibilityMap::Visibility visibility = humanPlayer->visibility->visibilityAt(entity->position());
        if (visibility == VisibilityMap::Unexplored) {
            continue;
        }

        if (entity->isUnit()) {
            Unit::Ptr unit = Entity::asUnit(entity);

            if (visibility == VisibilityMap::Visible) {
                entity->isVisible = true;
                visibleUnits.push_back(Entity::asUnit(entity));
                entity->renderer().render(*renderTarget->renderTarget_, camera->absoluteScreenPos(entity->position()), RenderType::Shadow);

                continue;
            }

            if (unit->playerId != GaiaID) {
                continue;
            }

            entity->isVisible = true;

            entity->renderer().render(*renderTarget->renderTarget_, camera->absoluteScreenPos(entity->position()), RenderType::InTheShadows);

            continue;
        }

        if (entity->isMissile()) {
            Missile::Ptr missile = Entity::asMissile(entity);
            if (visibility == VisibilityMap::Explored && missile->playerId != GaiaID) {
                continue;
            }

            entity->isVisible = true;

            MapPos shadowPosition = entity->position();
            shadowPosition.z = m_map->elevationAt(shadowPosition);
            entity->renderer().render(*renderTarget->renderTarget_, camera->absoluteScreenPos(shadowPosition), RenderType::Shadow);

            visibleMissiles.push_back(missile);

            continue;
        }

        if (entity->isDecayingEntity() || entity->isDoppleganger()) {
            if (visibility == VisibilityMap::Visible) {
                entity->renderer().render(*renderTarget->renderTarget_, camera->absoluteScreenPos(entity->position()), RenderType::Base);
            } else {
                entity->renderer().render(*renderTarget->renderTarget_, camera->absoluteScreenPos(entity->position()), RenderType::InTheShadows);
            }

            entity->isVisible = true;
        }
    }
    std::sort(visibleUnits.begin(), visibleUnits.end(), MapPositionSorter());


    m_outlineOverlay.clear(sf::Color::Transparent);

    for (const Unit::Ptr &unit : visibleUnits) {
        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position());
        if (!(unit->data()->OcclusionMode & genie::Unit::OccludeOthers)) {
            unit->renderer().render(m_outlineOverlay, unitPosition, RenderType::Outline);
        } else {
            unit->renderer().render(m_outlineOverlay, unitPosition, RenderType::BuildingAlpha);

        }
    }
    std::reverse(visibleUnits.begin(), visibleUnits.end());

    for (const Unit::Ptr &unit : visibleUnits) {

        const bool blinkingAsTarget = unit->targetBlinkTimeLeft > 0 &&
                (((unit->targetBlinkTimeLeft) / 500) % 2 == 0) &&
                !unit->isDead() && !unit->isDying();

        if (blinkingAsTarget || m_selectedUnits.count(unit)) { // draw health indicator
            sf::RectangleShape rect;
            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(1);

            double width = unit->data()->OutlineSize.x * Constants::TILE_SIZE_HORIZONTAL;
            double height =  unit->data()->OutlineSize.y * Constants::TILE_SIZE_VERTICAL;

            if (unit->data()->ObstructionType == genie::Unit::UnitObstruction) {
                width /= 2.;
                height /= 2.;
            } else {
                circle.setPointCount(4);
            }

#ifdef DEBUG
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setSize(unit->rect().size());
            rect.setPosition(camera->absoluteScreenPos(unit->position()) + unit->rect().topLeft());
            m_outlineOverlay.draw(rect);
#endif

            ScreenPos pos = camera->absoluteScreenPos(unit->position());

            circle.setPosition(pos.x - width, pos.y - height);
            circle.setRadius(width);
            circle.setScale(1, height / width);
            circle.setOutlineColor(sf::Color::Black);
            renderTarget->draw(circle);

            if (blinkingAsTarget) {
                circle.setOutlineColor(sf::Color::Green);
            } else {
                circle.setOutlineColor(sf::Color::White);
            }
            circle.setOutlineThickness(2);
            circle.setPosition(pos.x - width, pos.y - height + 1);
            renderTarget->draw(circle);


            if (!blinkingAsTarget) {
                pos.x -= Constants::TILE_SIZE_HORIZONTAL / 8;
                pos.y -= height + Constants::TILE_SIZE_HEIGHT * unit->data()->HPBarHeight;

                rect.setOutlineColor(sf::Color::Transparent);
                rect.setPosition(pos);

                if (unit->healthLeft() < 1.) {
                    rect.setFillColor(sf::Color::Red);
                    rect.setSize(sf::Vector2f(Constants::TILE_SIZE_HORIZONTAL / 4., 2));
                    m_outlineOverlay.draw(rect);
                }

                rect.setFillColor(sf::Color::Green);
                rect.setSize(sf::Vector2f(unit->healthLeft() * Constants::TILE_SIZE_HORIZONTAL / 4., 2));
                m_outlineOverlay.draw(rect);
            }
        }

        const ScreenPos pos = renderTarget->camera()->absoluteScreenPos(unit->position());
        unit->renderer().render(*renderTarget->renderTarget_, pos, RenderType::Base);


#ifdef DEBUG
        ActionPtr action = unit->currentAction();
        if (action && action->type == IAction::Type::Move) {
            std::shared_ptr<ActionMove> moveAction = std::static_pointer_cast<ActionMove>(action);

            sf::CircleShape circle;
            circle.setRadius(2);
//            circle.setScale(1, 0.5);
            circle.setFillColor(sf::Color::Black);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1);
            for (const MapPos &p : moveAction->path()) {
                ScreenPos pos = camera->absoluteScreenPos(p);
                circle.setPosition(pos.x, pos.y);
                m_outlineOverlay.draw(circle);
            }
        }
#endif
    }

    m_outlineOverlay.display();

    { // this is a bit wrong, on bright buildings it's almost not visible, but haven't found a better solution other than writing a custom shader
        sf::Sprite sprite;
        sprite.setTexture(m_outlineOverlay.getTexture());
        renderTarget->renderTarget_->draw(sprite, sf::BlendAdd);
    }

#ifdef DEBUG
    for (size_t i=0; i<ActionMove::testedPoints.size(); i++) {
        const MapPos &mpos = ActionMove::testedPoints[i];
        sf::CircleShape circle;
        ScreenPos pos = camera->absoluteScreenPos(mpos);
        circle.setPosition(pos.x, pos.y);
        circle.setRadius(2);
        int col = 128 * i / ActionMove::testedPoints.size() + 128;
        circle.setFillColor(sf::Color(128 + col, 255 - col, 255, 128));
        circle.setOutlineColor(sf::Color::Transparent);
        renderTarget->draw(circle);
    }
    for (const Unit::Ptr &unit : visibleUnits) {
        sf::CircleShape circle;
        ScreenPos pos = camera->absoluteScreenPos(unit->position());
        circle.setPosition(pos.x, pos.y);
        circle.setRadius(5);
        circle.setScale(1, 0.5);
        circle.setOutlineColor(sf::Color::White);
        renderTarget->draw(circle);
    }
#endif

    m_moveTargetMarker->renderer().render(*renderTarget->renderTarget_,
                                          renderTarget->camera()->absoluteScreenPos(m_moveTargetMarker->position()),
                                          RenderType::Base);

    for (const Missile::Ptr &missile : visibleMissiles) {
        missile->renderer().render(*renderTarget->renderTarget_, renderTarget->camera()->absoluteScreenPos(missile->position()), RenderType::Base);
    }

    if (m_state == State::PlacingBuilding || m_state == State::PlacingWall) {
//        DBG << "placing buildings" << m_buildingsToPlace.size();

        if (m_buildingsToPlace.size() == 1) {
            const double width = m_buildingsToPlace[0].data->OutlineSize.x * Constants::TILE_SIZE_HORIZONTAL + 1;
            const double height =  m_buildingsToPlace[0].data->OutlineSize.y * Constants::TILE_SIZE_VERTICAL + 1;

            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(1);
            circle.setRadius(width);
            circle.setPointCount(4);
            circle.setScale(1, height / width);

            ScreenPos pos = camera->absoluteScreenPos(m_buildingsToPlace[0].position);


            circle.setPosition(pos.x - width, pos.y - height + 1);
            circle.setOutlineColor(sf::Color::Black);
            renderTarget->draw(circle);

            circle.setPosition(pos.x - width, pos.y - height);
            circle.setOutlineColor(sf::Color::White);
            renderTarget->draw(circle);
        }

        for (const UnplacedBuilding &building : m_buildingsToPlace) {
            building.graphic->setOrientation(building.orientation);
            building.graphic->render(*renderTarget->renderTarget_,
                                        renderTarget->camera()->absoluteScreenPos(building.position),
                                        building.canPlace ? RenderType::ConstructAvailable : RenderType::ConstructUnavailable);
        }
    }
}

bool UnitManager::onLeftClick(const ScreenPos &screenPos, const CameraPtr &camera)
{
    Player::Ptr humanPlayer = m_humanPlayer.lock();
    if (!humanPlayer) {
        WARN << "human player gone";
        return false;
    }

    switch (m_state) {
    case State::PlacingBuilding: {
        if (m_buildingsToPlace.empty()) {
            WARN << "no buildings to place while placing buildings!";
            m_state = State::Default;
            return false;
        }
        if (m_buildingsToPlace[0].isWall) {
            m_wallPlacingStart = camera->absoluteMapPos(screenPos);
            m_state = State::PlacingWall;
            return true;
        }

        if (m_buildingsToPlace.size() != 1) {
            WARN << "more than one building to place, and it's not a wall";
        }

        placeBuilding(m_buildingsToPlace[0]);
        m_buildingsToPlace.clear();

        m_state = State::Default;
        return true;
    }
    case State::SelectingAttackTarget: {
        DBG << "Selecting attack target";
        MapPos targetPos = camera->absoluteMapPos(screenPos);
        Unit::Ptr targetUnit = unitAt(screenPos, camera);
        if (targetUnit && targetUnit->playerId == humanPlayer->playerId) {
            targetUnit.reset();
        }
        for (const Unit::Ptr &unit : m_selectedUnits) {
            if (unit->playerId != humanPlayer->playerId) {
                continue;
            }



            std::shared_ptr<ActionAttack> action;
            if (targetUnit) {
                action = std::make_shared<ActionAttack>(unit, targetUnit, unit->findMatchingTask(genie::Task::Attack, targetUnit->data()->ID));
            } else {
                action = std::make_shared<ActionAttack>(unit, targetPos, unit->findMatchingTask(genie::Task::Attack, -1));
            }
            unit->setCurrentAction(action);
        }
        break;
    }
    case State::Default:
        return false;
    default:
        break;
    }

    m_state = State::Default;
    return true;
}

void UnitManager::onRightClick(const ScreenPos &screenPos, const CameraPtr &camera)
{
    m_buildingsToPlace.clear();

    if (m_selectedUnits.empty()) {
        return;
    }

    Player::Ptr humanPlayer = m_humanPlayer.lock();
    if (!humanPlayer) {
        WARN << "human player gone";
        return;
    }

    // Thanks task swap group satan
    bool foundTasks = false;
    for (const Unit::Ptr &unit : m_selectedUnits) {
        if (unit->playerId != humanPlayer->playerId) {
            continue;
        }
        Task task = taskForPosition(unit, screenPos, camera);
        if (!task.data) {
            continue;
        }

        if (task.data->ActionType == genie::Task::Combat) {
            AudioPlayer::instance().playSound(unit->data()->Action.AttackSound, humanPlayer->civilization.id());
        }

        unit->clearActionQueue();
        Unit::Ptr target = unitAt(screenPos, camera);
        IAction::assignTask(task, unit, target);
        if (target) {
            target->targetBlinkTimeLeft = 3000; // 3s
        }
        foundTasks = true;
    }

    if (foundTasks) {
        return;
    }


    const MapPos mapPos = camera->absoluteMapPos(screenPos);
    bool movedSomeone = false;
    for (const Unit::Ptr &unit : m_selectedUnits) {
        if (unit->playerId != humanPlayer->playerId) {
            continue;
        }

        unit->clearActionQueue();
        moveUnitTo(unit, mapPos);
        movedSomeone = true;

        AudioPlayer::instance().playSound(unit->data()->Action.MoveSound, humanPlayer->civilization.id());
    }

    if (movedSomeone) {
        m_moveTargetMarker->moveTo(mapPos);
    }
}

void UnitManager::onMouseMove(const MapPos &mapPos)
{
    if (m_buildingsToPlace.empty()) {
        return;
    }

    if (m_state == State::PlacingWall) {
        MapPos startTile = (m_wallPlacingStart / Constants::TILE_SIZE).rounded();
        startTile.clamp(Size(m_map->getCols(), m_map->getRows()));

        MapPos endTile = (mapPos / Constants::TILE_SIZE).rounded();
        endTile.clamp(Size(m_map->getCols(), m_map->getRows()));

        // Is the angle between the start and end less than 0.1 radians away from 45° (aka. M_PI / 4) from any quadrant?
        const bool diagonal = std::abs(std::abs(std::fmod(startTile.angleTo(endTile), M_PI_2)) - M_PI_2 / 2.) < 0.1;

        const size_t tileCount = std::max<size_t>(diagonal ? startTile.distance(endTile) : startTile.manhattanDistance(endTile), 1);
        if (tileCount > m_buildingsToPlace.size()) {
            for (size_t i = m_buildingsToPlace.size(); i < tileCount; i++) {
                m_buildingsToPlace.emplace_back(m_buildingsToPlace[0]); // duplicate
            }
        } else {
            // Shrink
            m_buildingsToPlace.resize(tileCount);
        }
        assert(tileCount == m_buildingsToPlace.size());
        assert(tileCount > 0);

        size_t index = 0;

        const int startX = startTile.x < endTile.x ? startTile.x : endTile.x;
        const int startY = startTile.y < endTile.y ? startTile.y : endTile.y;
        const int endX = startTile.x < endTile.x ? endTile.x : startTile.x;
        const int endY = startTile.y < endTile.y ? endTile.y : startTile.y;

        if (diagonal) {
            int x = startTile.x;
            int y = startTile.y;
            int dx = startTile.x < endTile.x ? 1 : -1;
            int dy = startTile.y < endTile.y ? 1 : -1;

            // Magic values
            const int orientation = dx == dy ? 3 : 4;

            for (index = 0; index < m_buildingsToPlace.size(); index++) {
                m_buildingsToPlace[index].position = MapPos(x, y);
                m_buildingsToPlace[index].orientation = orientation;

                x += dx;
                y += dy;
            }
        } else if (std::abs(startTile.x - endTile.x) > std::abs(startTile.y - endTile.y)) {
            for (int x = startX; x < endX; x++) {
                m_buildingsToPlace[index].orientation = 1;
                m_buildingsToPlace[index++].position = MapPos(startTile.x < endTile.x ?  x : x + 1, startTile.y); // im probably dumb, but this works for now
            }
            if (index > 0) {
                m_buildingsToPlace[index - 1].orientation = 2;
            }

            for (int y = startY; y < endY; y++) {
                m_buildingsToPlace[index].orientation = 0;
                m_buildingsToPlace[index++].position = MapPos(endTile.x, y);
            }
        } else {
            for (int x = startX; x < endX; x++) {
                m_buildingsToPlace[index].orientation = 1;
                m_buildingsToPlace[index++].position = MapPos(x, endTile.y);
            }
            if (index > 0) {
                m_buildingsToPlace[index - 1].orientation = 2;
            }

            for (int y = startY; y < endY; y++) {
                m_buildingsToPlace[index].orientation = 0;
                m_buildingsToPlace[index++].position = MapPos(startTile.x, startTile.y < endTile.y ? y : y + 1); // im probably dumb, but this works for now x2
            }
        }
        m_buildingsToPlace.front().orientation = 2;
        m_buildingsToPlace.back().orientation = 2;

        // Do it in another pass here, makes the code above a bit more readable
        for (UnplacedBuilding &building : m_buildingsToPlace) {
            building.position *= Constants::TILE_SIZE;
        }
    } else {
        m_buildingsToPlace[0].position = mapPos;
    }

    for (UnplacedBuilding &building : m_buildingsToPlace) {
        building.position = Unit::snapPositionToGrid(building.position, m_map, building.data);
        building.canPlace = Building::canPlace(building.position, m_map, building.data);
    }
}

bool UnitManager::onMouseRelease()
{
    if (m_buildingsToPlace.empty()) {
        return false;
    }

    for (const UnplacedBuilding &building : m_buildingsToPlace) {
        placeBuilding(building);
    }
    m_buildingsToPlace.clear();

    return true;
}

void UnitManager::selectUnits(const ScreenRect &selectionRect, const CameraPtr &camera)
{
    if (!m_buildingsToPlace.empty()) {
        return;
    }

    const UnitSet previouslySelected = std::move(m_selectedUnits);

    m_currentActions.clear();

    Player::Ptr humanPlayer = m_humanPlayer.lock();
    if (!humanPlayer) {
        WARN << "human player gone";
        return;
    }

    std::vector<Unit::Ptr> containedUnits;
    bool hasHumanPlayer = false;
    int8_t requiredInteraction = genie::Unit::ObjectInteraction;
    const bool isClick = selectionRect.width < 10 && selectionRect.height < 10;

    for (const Unit::Ptr &unit : m_units) {
        const ScreenPos absoluteUnitPosition = camera->absoluteScreenPos(unit->position());
        if (!selectionRect.overlaps(unit->rect() + absoluteUnitPosition)) {
            continue;
        }
        if (isClick && !unit->checkClick(selectionRect.bottomRight() - absoluteUnitPosition)) {
            continue;
        }
        hasHumanPlayer = hasHumanPlayer || unit->playerId == humanPlayer->playerId;

        requiredInteraction = std::max(unit->data()->InteractionMode, requiredInteraction);
        containedUnits.push_back(unit);
    }

    UnitSet newSelection;

    for (const Unit::Ptr &unit : containedUnits) {
        if (unit->data()->InteractionMode < requiredInteraction) {
            continue;
        }
        if (hasHumanPlayer && unit->playerId != humanPlayer->playerId) {
            continue;
        }

        newSelection.insert(unit);
    }

    UnitSet newlySelected;
    if (isClick) {
        if (!newSelection.empty()) {
            const Unit::Ptr mostVisibleUnit = *std::min_element(newSelection.begin(), newSelection.end(), MapPositionSorter());
            if (!previouslySelected.count(mostVisibleUnit)) {
                newlySelected.insert(mostVisibleUnit);
            }
        }
    } else {
        for (const Unit::Ptr &unit : newSelection) {
            if (!previouslySelected.count(unit)) {
                newlySelected.insert(unit);
            }
        }
    }

    for (const Unit::Ptr &unit : newlySelected) {
        DBG << "Selected" << unit->debugName << unit->id;
        EventManager::unitSelected(unit.get());
    }

    for (const Unit::Ptr &unit : previouslySelected) {
        if (!newlySelected.count(unit)) {
            DBG << "Deselected" << unit->debugName << unit->id;
            EventManager::unitDeselected(unit.get());
        }
    }

    if (newSelection.empty()) {
        DBG << "Unable to find anything to select in " << selectionRect;
        return;
    }


    if (isClick) {
        const Unit::Ptr mostVisibleUnit = *std::min_element(newSelection.begin(), newSelection.end(), MapPositionSorter());
        setSelectedUnits({std::move(mostVisibleUnit)});
    } else {
        setSelectedUnits(std::move(newSelection));
    }
}

void UnitManager::setMap(const MapPtr &map)
{
    m_map = map;
}

void UnitManager::setSelectedUnits(const UnitSet &units)
{
    m_selectedUnits = units;
    m_currentActions.clear();
    m_buildingsToPlace.clear();

    if (units.empty()) {
        return;
    }

    for (const Unit::Ptr &unit : m_selectedUnits) {
        m_currentActions.merge(unit->availableActions());
    }

    // Not sure what is the actual correct behavior here:
    // If all units are the same type, do we play "their" sound,
    // or do we only play it if there's only one selected unit
#if 1
    if (m_selectedUnits.size() == 1) {
        playSound(*m_selectedUnits.begin());
    }
#else
    int selectionSound = (*units.begin())->data()->SelectionSound;
    for (const Unit::Ptr &unit : units) {
        if (unit->data()->SelectionSound == -1) {
            continue;
        }

        if (selectionSound == -1) {
            selectionSound = unit->data()->SelectionSound;
            continue;
        }

        if (selectionSound != unit->data()->SelectionSound) {
            selectionSound = -1;
            break;
        }
    }

    if (selectionSound != -1) {
        AudioPlayer::instance().playSound(selectionSound, (*units.begin())->civilization->id());
    }
#endif
}

void UnitManager::startPlaceBuilding(const int unitId, const std::shared_ptr<Player> &player)
{
    DBG << "starting to place unit" << unitId;
    m_buildingsToPlace.clear();

    UnplacedBuilding toPlace;
    toPlace.unitID = unitId;
    toPlace.data = &player->civilization.unitData(unitId);
    toPlace.isWall = toPlace.data->Class == genie::Unit::Wall;
    DBG << "is wall?" << toPlace.isWall;
    if (unitId == Unit::Farm) { // Farms are very special (shortbus special), so better to just use a special class
        DBG << "placing a farm";
        toPlace.graphic = std::make_shared<FarmRender>(Size(toPlace.data->Size));
    } else {
        toPlace.graphic = std::make_shared<GraphicRender>();
        toPlace.graphic->setGraphic(toPlace.data->StandingGraphic.first);
    }

    m_buildingsToPlace.push_back(std::move(toPlace));
    m_state = State::PlacingBuilding;
}

void UnitManager::enqueueProduceUnit(const genie::Unit *unitData, const UnitSet &producers)
{
    if (producers.empty()) {
        WARN << "Handed no producers";
        return;
    }

    Building::Ptr producer = Unit::asBuilding(*producers.begin());
    if (!producer) {
        WARN << "Invalid producer";
        return;
    }

    producer->enqueueProduceUnit(unitData);
}

void UnitManager::enqueueResearch(const genie::Tech *techData, const UnitSet &producers)
{
    if (producers.empty()) {
        WARN << "Handed no producers";
        return;
    }

    Building::Ptr producer = Unit::asBuilding(*producers.begin());
    if (!producer) {
        WARN << "Invalid producer";
        return;
    }

    producer->enqueueProduceResearch(techData);
}

Unit::Ptr UnitManager::unitAt(const ScreenPos &pos, const CameraPtr &camera) const
{
    for (const Unit::Ptr &unit : m_units) {
        if (!unit->isVisible) {
            continue;
        }

        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position());
        const ScreenRect unitRect = unit->rect() + unitPosition;
        if (unitRect.contains(pos)) {
            return unit;
        }
    }

    return nullptr;
}

Unit::Ptr UnitManager::clickedUnitAt(const ScreenPos &pos, const CameraPtr &camera)
{
    Unit::Ptr unit = unitAt(pos, camera);
    if (!unit) {
        return nullptr;
    }
    const ScreenPos relativePosition = pos - camera->absoluteScreenPos(unit->position());
    if (!unit->checkClick(relativePosition)) {
        return nullptr;
    }
    return unit;
}

const Task UnitManager::defaultActionAt(const ScreenPos &pos, const CameraPtr &camera) const noexcept
{
    if (m_selectedUnits.empty()) {
        return Task();
    }

    Unit::Ptr target = unitAt(pos, camera);
    if (!target) {
        return Task();
    }

    // One of the selected themselves
    if (m_selectedUnits.count(target)) {
        return Task();
    }

    return IAction::findMatchingTask(m_humanPlayer.lock(), target, m_currentActions);
}

void UnitManager::moveUnitTo(const Unit::Ptr &unit, const MapPos &targetPos)
{
    unit->setCurrentAction(ActionMove::moveUnitTo(unit, targetPos));
}

void UnitManager::selectAttackTarget()
{
    m_state = State::SelectingAttackTarget;
}

void UnitManager::placeBuilding(const UnplacedBuilding &building)
{
    if (!building.canPlace) {
        DBG << "Can't place this building";
        return;
    }

    Unit::Ptr unit = UnitFactory::Inst().createUnit(building.unitID, building.position, m_humanPlayer.lock(), *this);
    Building::Ptr buildingToPlace = Unit::asBuilding(unit);

    DBG << "placing bulding";
    if (!buildingToPlace) {
        WARN << "Can't place null building";
        return;
    }

    Player::Ptr humanPlayer = m_humanPlayer.lock();
    if (!humanPlayer) {
        WARN << "human player gone";
        return;
    }

    buildingToPlace->isVisible = true;
    add(buildingToPlace);
    buildingToPlace->setCreationProgress(0);

    for (const Unit::Ptr &unit : m_selectedUnits) {
        if (unit->playerId != humanPlayer->playerId) {
            continue;
        }

        Task task;
        for (const Task &potential : unit->availableActions()) {
            if (potential.data->ActionType == genie::Task::Build) {
                task = potential;
                break;
            }
        }
        if (!task.data) {
            continue;
        }

        // TODO: should clear this elsewhere, otherwise it just gets queued up
//        unit->clearActionQueue();
        IAction::assignTask(task, unit, buildingToPlace);
    }
}

void UnitManager::playSound(const Unit::Ptr &unit)
{
    const int id = unit->data()->SelectionSound;
    if (id < 0) {
        DBG << "no selection sound for" << unit->debugName;
        return;
    }

    Player::Ptr player = unit->player.lock();
    if (player) {
        AudioPlayer::instance().playSound(id, player->civilization.id());
    } else {
        WARN << "Lost the player";
    }
}

const Task UnitManager::taskForPosition(const Unit::Ptr &unit, const ScreenPos &pos, const CameraPtr &camera) const noexcept
{
    if (m_selectedUnits.empty()) {
        return Task();
    }

    Unit::Ptr target = unitAt(pos, camera);
    if (!target) {
        return Task();
    }

    // One of the selected themselves
    if (m_selectedUnits.count(target)) {
        return Task();
    }

    return IAction::findMatchingTask(m_humanPlayer.lock(), target, unit->availableActions());
}
