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

#include "render/Camera.h"

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
#include "resource/Sprite.h"
#include "Map.h"

#include <genie/Types.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/Action.h>

#include <algorithm>
#include <utility>

namespace genie {
class Tech;
}  // namespace genie

UnitManager::UnitManager()
{
    EventManager::registerListener(this, EventManager::ResearchComplete);
    EventManager::registerListener(this, EventManager::TileHidden);
    EventManager::registerListener(this, EventManager::TileDiscovered);
//    EventManager::registerListener(this, EventManager::PlayerResourceChanged); // TODO auto actions that cost things
}

UnitManager::~UnitManager()
{
}

void UnitManager::add(const Unit::Ptr &unit, const MapPos &position)
{
    if (IS_UNLIKELY(!unit)) {
        WARN << "trying to add null unit";
        return;
    }
    unit->setMap(m_map);
    unit->setPosition(position, true);
    m_units.push_back(unit);
    if (unit->actions.hasAutoTargets()) {
        // stl is shit
        m_unitsWithActions.add(unit);
    }

    EventManager::unitCreated(unit.get());
}

void UnitManager::remove(const Unit::Ptr &unit)
{
    // Could just mark it as dead, but don't want a corpse, I think
    if (m_selectedUnits.contains(unit)) {
        EventManager::unitDeselected(unit.get());
        m_selectedUnits.remove(unit);
    }

    m_unitsWithActions.remove(unit);

    UnitVector::iterator it = std::find(m_units.begin(), m_units.end(), unit);
    if (it != m_units.end()) {
        EventManager::unitDying(unit.get()); // not sure about this, but whatever
        m_units.erase(it);
    }

    // Check if the human player saw it, and in that case notify it
    // TODO: non-human players, we need to check all visibility maps
    std::shared_ptr<Player> humanPlayer = m_humanPlayer.lock();
    REQUIRE(humanPlayer, return);
    if (humanPlayer->visibility->visibilityAt(unit->position()) == VisibilityMap::Visible) {
        EventManager::unitDisappeared(humanPlayer.get(), unit.get()); // good thing this is synchronous, I hate raw pointers
    }
    m_availableActionsChanged = true;
}

void UnitManager::onUnitMoved(Unit *unit, const MapPos &oldTile, const MapPos &newTile)
{
    if (unit->playerId() == m_humanPlayerID) {
        DBG << "Was human player" << unit->debugName;
        return;
    }

    Player::Ptr human = m_humanPlayer.lock();
    REQUIRE(human, return);

    const VisibilityMap::Visibility oldVisibility = human->visibility->visibilityAt(oldTile);
    if (oldVisibility == VisibilityMap::Unexplored) {
        WARN << "old was unexplored";
        return;
    }
    const VisibilityMap::Visibility newVisibility = human->visibility->visibilityAt(newTile);
    if (newVisibility == VisibilityMap::Unexplored) {
        WARN << "new was unexplored";
        return;
    }

    if (oldVisibility == VisibilityMap::Visible && newVisibility == VisibilityMap::Explored) {
        return;
    }
}

void UnitManager::onTileHidden(const int playerID, const int tileX, const int tileY)
{
    // TODO: this should be tracked by player? just care for the human for now
    std::vector<std::weak_ptr<Entity>> entities = m_map->entitiesAt(tileX, tileY);
    for (const std::weak_ptr<Entity> &e : entities) {
        Unit::Ptr unit = Unit::fromEntity(e);
        if (!unit) {
            continue;
        }
        if (unit->playerId() == playerID) {
            continue;
        }

        WARN << "Creating doppleganger at" << tileX << tileY << "for" << unit->debugName;
        addStaticEntity(UnitFactory::createDopplegangerFor(unit));
        unit->isVisible = true;
    }
}

void UnitManager::onTileDiscovered(const int playerID, const int tileX, const int tileY)
{
    std::unordered_set<StaticEntity::Ptr>::iterator staticEntityIterator = m_staticEntities.begin();
    while (staticEntityIterator != m_staticEntities.end()) {
        const StaticEntity::Ptr &entity = *staticEntityIterator;

        const MapPos tilePos = entity->position() / Constants::TILE_SIZE;
        if (tilePos.x != tileX || tilePos.y != tileY) {
            staticEntityIterator++;
            continue;
        }
        if (!entity->isDoppleganger()) {
            staticEntityIterator++;
            continue;
        }

        DopplegangerEntity::Ptr doppleganger = DopplegangerEntity::fromEntity(entity);
        if (doppleganger->ownerID == playerID) {
            staticEntityIterator++;
            continue;
        }

        bool visibleByAll = true;
        for (const std::weak_ptr<Player> &weakPlayer : m_players) {
            Player::Ptr player = weakPlayer.lock();
            REQUIRE(player, continue);

            if (!player->canSeeUnitsFor(playerID)) {
                visibleByAll = false;
                break;
            }
        }

        // If someone still only see the doppleganger, keep it
        if (!visibleByAll) {
            staticEntityIterator++;
        } else {
            // TODO: visibility of corpses
            staticEntityIterator = m_staticEntities.erase(staticEntityIterator);
        }
    }
}

bool UnitManager::init()
{
    m_moveTargetMarker = std::make_unique<MoveTargetMarker>();
//    m_moveTargetMarker->setMap(m_map);

    return true;
}

void UnitManager::setPlayers(const std::vector<std::shared_ptr<Player>> &players)
{
    for (const std::shared_ptr<Player> &player : players) {
        m_players.emplace_back(player);
    }
}

void UnitManager::setHumanPlayer(const std::shared_ptr<Player> &player)
{
    m_humanPlayer = player;
    m_humanPlayerID = player->playerId;
}

bool UnitManager::update(Time time)
{
    bool updated = false;

    if (m_unitsMoved) {
        m_unitsMoved = false;

        for (const Unit::Ptr &unit : m_unitsWithActions) {
            Task task = unit->actions.checkForAutoTargets();
            if (!task.data) {
                continue;
            }
            IAction::assignTask(task, unit, IAction::AssignType::Replace);
        }
    }

    if (m_availableActionsChanged) {
        m_availableActionsChanged = false;
        updateAvailableActions();
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

    // Update decaying entities (smoke stuff from siege, corpses, etc.) as well as the doppelgangers
    std::unordered_set<StaticEntity::Ptr>::iterator staticEntityIterator = m_staticEntities.begin();
    while (staticEntityIterator != m_staticEntities.end()) {
        const StaticEntity::Ptr &entity = *staticEntityIterator;
        updated = entity->update(time) || updated;
        if (entity->shouldBeRemoved()) {
            staticEntityIterator = m_staticEntities.erase(staticEntityIterator);
            updated = true;
        } else {
            staticEntityIterator++;
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
            unit->selected = false;
            m_selectedUnits.remove(unit);
            EventManager::unitDeselected(unit.get());
            m_unitsWithActions.remove(unit);
            m_availableActionsChanged = true;
        }

        if (isDead) {
            EventManager::unitDying(unit.get());

            DecayingEntity::Ptr corpse = UnitFactory::Inst().createCorpseFor(unit);
            if (corpse) {
                m_staticEntities.insert(corpse);
                updated = true;
            }

            unitIterator = m_units.erase(unitIterator);
        } else {
            // Update the living units that are left
            updated = unit->update(time) || updated;
            unitIterator++;
        }
    }

    updated = m_moveTargetMarker->update(time) || updated;

    return updated;
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
        if (targetUnit && targetUnit->playerId() == humanPlayer->playerId) {
            targetUnit.reset();
        }
        for (const Unit::Ptr &unit : m_selectedUnits) {
            if (unit->playerId() != humanPlayer->playerId) {
                continue;
            }



            std::shared_ptr<ActionAttack> action;
            if (targetUnit) {
                Task task = unit->actions.findAnyTask(genie::ActionType::Attack, targetUnit->data()->ID);
                task.target = targetUnit;
                action = std::make_shared<ActionAttack>(unit, task);
            } else {
                DBG << "Attacking ground";
                action = std::make_shared<ActionAttack>(unit, targetPos, unit->actions.findAnyTask(genie::ActionType::Attack, -1));
            }
            unit->actions.setCurrentAction(action);
        }
        break;
    }
    case State::SelectingGarrisonTarget: {
        DBG << "Selecting garrison target";
        Unit::Ptr targetUnit = unitAt(screenPos, camera);
        if (!targetUnit || !humanPlayer->isAllied(targetUnit->playerId())) {
            WARN << "No valid unit at selected position";
            break;
        }
        for (const Unit::Ptr &unit : m_selectedUnits) {
            if (unit->playerId() != humanPlayer->playerId) {
                continue;
            }

            Task garrison = unit->actions.findAnyTask(genie::ActionType::Garrison, targetUnit->data()->ID);
            if (!garrison.data) {
                continue;
            }
            garrison.target = targetUnit;
            IAction::assignTask(garrison, unit, IAction::AssignType::Replace);
        }
        break;
    }
    case State::Default:
        return false;
    default:
        WARN << "Unhandled state" << m_state;
        break;
    }

    m_state = State::Default;
    return true;
}

void UnitManager::onRightClick(const ScreenPos &screenPos, const CameraPtr &camera)
{
    m_buildingsToPlace.clear();

    if (m_selectedUnits.isEmpty()) {
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
        if (unit->playerId() != humanPlayer->playerId) {
            continue;
        }
        Task task = taskForPosition(unit, screenPos, camera);
        if (!task.data) {
            continue;
        }

        if (task.data->ActionType == genie::ActionType::Combat) {
            AudioPlayer::instance().playSound(unit->data()->Action.AttackSound, humanPlayer->civilization.id());
        }

        Unit::Ptr target = unitAt(screenPos, camera);
        task.target = target;
        IAction::assignTask(task, unit, IAction::AssignType::Replace);
        if (target) {
            target->targetBlinkTimeLeft = 3000; // 3s
        }
        foundTasks = true;
    }

    if (foundTasks) {
        return;
    }


    MapPos mapPos = camera->absoluteMapPos(screenPos).clamped(m_map->pixelSize());

    bool movedSomeone = false;
    for (const Unit::Ptr &unit : m_selectedUnits) {
        if (unit->playerId() != humanPlayer->playerId) {
            continue;
        }

        unit->actions.clearActionQueue();
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
        startTile.clamp(Size(m_map->columnCount(), m_map->rowCount()));

        MapPos endTile = (mapPos / Constants::TILE_SIZE).rounded();
        endTile.clamp(Size(m_map->columnCount(), m_map->rowCount()));

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
        building.position = m_map->snapPositionToGrid(building.position, Size(building.data->Size));
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

    m_currentActions.tasks.clear();

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
        if (!unit->isVisible) {
            continue;
        }

        const ScreenPos absoluteUnitPosition = camera->absoluteScreenPos(unit->position());
        if (!selectionRect.overlaps(unit->screenRect() + absoluteUnitPosition)) {
            continue;
        }
        if (isClick && !unit->checkClick(selectionRect.bottomRight() - absoluteUnitPosition)) {
            continue;
        }
        hasHumanPlayer = hasHumanPlayer || unit->playerId() == humanPlayer->playerId;

        requiredInteraction = std::max(unit->data()->InteractionMode, requiredInteraction);
        containedUnits.push_back(unit);
    }

    UnitSet newSelection;

    for (const Unit::Ptr &unit : containedUnits) {
        if (unit->data()->InteractionMode < requiredInteraction) {
            continue;
        }
        if (hasHumanPlayer && unit->playerId() != humanPlayer->playerId) {
            //continue;
        }

        newSelection.add(unit);
    }

    UnitSet newlySelected;
    if (isClick) {
        if (!newSelection.isEmpty()) {
            const Unit::Ptr mostVisibleUnit = *std::min_element(newSelection.begin(), newSelection.end(), MapPositionSorter());
            if (!previouslySelected.contains(mostVisibleUnit)) {
                newlySelected.add(mostVisibleUnit);
            }
        }
    } else {
        for (const Unit::Ptr &unit : newSelection) {
            if (!previouslySelected.contains(unit)) {
                newlySelected.add(unit);
            }
        }
    }

    for (const Unit::Ptr &unit : newlySelected) {
        unit->selected = true;
        DBG << "Selected" << unit->debugName << unit->id;
        EventManager::unitSelected(unit.get());
    }

    for (const Unit::Ptr &unit : previouslySelected) {
        if (!newlySelected.contains(unit)) {
            unit->selected = false;
            DBG << "Deselected" << unit->debugName << unit->id;
            EventManager::unitDeselected(unit.get());
        }
    }

    if (newSelection.isEmpty()) {
        DBG << "Unable to find anything to select in " << selectionRect;
        return;
    }


    if (isClick) {
        const Unit::Ptr mostVisibleUnit = *std::min_element(newSelection.begin(), newSelection.end(), MapPositionSorter());
        setSelectedUnits({std::move(mostVisibleUnit)});
    } else {
        setSelectedUnits(std::move(newSelection.units));
    }
}

void UnitManager::setMap(const MapPtr &map)
{
    m_map = map;
}

void UnitManager::updateAvailableActions()
{
    m_currentActions.tasks.clear();

    std::unordered_set<Task> updated;
    for (const Unit::Ptr &unit : m_selectedUnits) {
        const TaskSet tasks = unit->actions.availableActions();
        updated.merge(std::unordered_set<Task>(tasks.begin(), tasks.end()));
    }
    m_currentActions.tasks = std::vector<Task>(updated.begin(), updated.end());

    emit(ActionsChanged);
}

void UnitManager::setSelectedUnits(const UnitVector &units)
{
    m_selectedUnits.units = units;
    m_buildingsToPlace.clear();
    m_availableActionsChanged = true;

    if (m_selectedUnits.isEmpty()) {
        return;
    }

    // Not sure what is the actual correct behavior here:
    // If all units are the same type, do we play "their" sound,
    // or do we only play it if there's only one selected unit
#if 1
    if (m_selectedUnits.size() == 1) {
        playSound(m_selectedUnits.first());
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
    if (!player) {
        WARN << "Can't place building without player!";
        return;
    }

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
        toPlace.graphic->setSprite(toPlace.data->StandingGraphic.first);
    }

    m_buildingsToPlace.push_back(std::move(toPlace));
    m_state = State::PlacingBuilding;
}

void UnitManager::enqueueProduceUnit(const genie::Unit *unitData, const UnitVector &producers)
{
    if (producers.empty()) {
        WARN << "Handed no producers";
        return;
    }

    Building::Ptr producer = Unit::asBuilding(producers[0]);
    if (!producer) {
        WARN << "Invalid producer";
        return;
    }

    producer->enqueueProduceUnit(unitData);
}

void UnitManager::enqueueResearch(const genie::Tech *techData, const UnitVector &producers)
{
    if (producers.empty()) {
        WARN << "Handed no producers";
        return;
    }

    Building::Ptr producer = Unit::asBuilding(producers[0]);
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
        const ScreenRect unitRect = unit->screenRect() + unitPosition;
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
    if (m_selectedUnits.isEmpty()) {
        return Task();
    }

    Unit::Ptr target = unitAt(pos, camera);
    if (!target) {
        return Task();
    }

    // One of the selected themselves
    if (m_selectedUnits.contains(target)) {
        return Task();
    }

    return UnitActionHandler::findMatchingTask(m_humanPlayer.lock(), target, m_currentActions);
}

void UnitManager::moveUnitTo(const Unit::Ptr &unit, const MapPos &targetPos)
{
    unit->actions.setCurrentAction(ActionMove::moveUnitTo(unit, targetPos));
}

void UnitManager::selectAttackTarget()
{
    m_state = State::SelectingAttackTarget;
}

void UnitManager::selectGarrisonTarget()
{
    m_state = State::SelectingGarrisonTarget;
}

void UnitManager::placeBuilding(const UnplacedBuilding &building)
{
    if (!building.canPlace) {
        DBG << "Can't place this building";
        return;
    }

    Unit::Ptr unit = UnitFactory::Inst().createUnit(building.unitID, m_humanPlayer.lock(), *this);
    Building::Ptr buildingToPlace = Unit::asBuilding(unit);

    if (!buildingToPlace) {
        WARN << "Can't place null building";
        return;
    }

    DBG << "placing bulding";

    Player::Ptr humanPlayer = m_humanPlayer.lock();
    if (!humanPlayer) {
        WARN << "human player gone";
        return;
    }

    if (!humanPlayer->canAffordUnit(building.unitID)) {
        WARN << "Player can't afford this";
        return;
    }

    humanPlayer->payForUnit(building.unitID);

    buildingToPlace->isVisible = true;
    add(buildingToPlace, building.position);
    buildingToPlace->setCreationProgress(0);
    DBG << building.orientation;
    if (building.graphic->sprite()) {
        unit->setAngle(building.graphic->sprite()->orientationToAngle(building.orientation));
    } else {
        WARN << "No graphic set for" << buildingToPlace->debugName;
    }
    DBG << unit->angle();

    for (const Unit::Ptr &selectedUnit : m_selectedUnits) {
        if (selectedUnit->playerId() != humanPlayer->playerId) {
            continue;
        }

        Task task;
        for (const Task &potential : selectedUnit->actions.availableActions()) {
            if (potential.data->ActionType == genie::ActionType::Build) {
                task = potential;
                break;
            }
        }
        if (!task.data) {
            continue;
        }

        task.target = buildingToPlace;
        IAction::assignTask(task, selectedUnit, IAction::AssignType::Replace);
    }
}

void UnitManager::playSound(const Unit::Ptr &unit)
{
    const int id = unit->data()->SelectionSound;
    if (id < 0) {
        DBG << "no selection sound for" << unit->debugName;
        return;
    }

    Player::Ptr player = unit->player().lock();
    if (player) {
        AudioPlayer::instance().playSound(id, player->civilization.id());
    } else {
        WARN << "Lost the player";
    }
}

const Task UnitManager::taskForPosition(const Unit::Ptr &unit, const ScreenPos &pos, const CameraPtr &camera) const noexcept
{
    if (m_selectedUnits.isEmpty()) {
        return Task();
    }

    Unit::Ptr target = unitAt(pos, camera);
    if (!target) {
        return Task();
    }

    // One of the selected themselves
    if (m_selectedUnits.contains(target)) {
        return Task();
    }

    return unit->actions.findTaskWithTarget(target);
}
