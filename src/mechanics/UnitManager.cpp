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

#include "ActionMove.h"
#include "ActionGather.h"
#include "ActionBuild.h"
#include "render/SfmlRenderTarget.h"
#include "resource/LanguageManager.h"
#include "global/Constants.h"
#include "resource/DataManager.h"
#include "Civilization.h"
#include "UnitFactory.h"
#include "audio/AudioPlayer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
}

void UnitManager::add(const Unit::Ptr &unit)
{
    m_units.insert(unit);
}

bool UnitManager::init()
{
    m_moveTargetMarker = std::make_shared<MoveTargetMarker>(m_map);

    return true;
}

bool UnitManager::update(Time time)
{
    bool updated = false;

    for (const Unit::Ptr &unit : m_units) {
        updated = unit->update(time) || updated;
    }

    updated = m_moveTargetMarker->update(time) || updated;

    return updated;
}

void UnitManager::render(const std::shared_ptr<SfmlRenderTarget> &renderTarget)
{
    CameraPtr camera = renderTarget->camera();

    if (camera->targetPosition() != m_previousCameraPos || m_outlineOverlay.getSize().x == 0) {
        updateVisibility(camera);
        m_previousCameraPos = camera->targetPosition();
    }

    if (Size(m_outlineOverlay.getSize()) != renderTarget->getSize()) {
        m_outlineOverlay.create(renderTarget->getSize().width, renderTarget->getSize().height);
    }

    m_outlineOverlay.clear(sf::Color::Transparent);

    for (const Unit::Ptr &unit : m_units) {
        if (!(unit->data()->OcclusionMode & genie::Unit::OccludeOthers)) {
            continue;
        }
        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position());

        for (const Unit::Annex &annex : unit->annexes) {
            if (!annex.unit->isVisible) {
                continue;
            }
            annex.unit->renderer().render(m_outlineOverlay,
                                          renderTarget->camera()->absoluteScreenPos(unit->position() + annex.offset),
                                          RenderType::Base
                                          );
        }
        if (unit->isVisible) {
            unit->renderer().render(m_outlineOverlay, unitPosition, RenderType::Base);
        }
    }

    for (const Unit::Ptr &unit : m_units) {
        if (!unit->isVisible) {
            continue;
        }

        if (m_selectedUnits.count(unit)) { // draw health indicator
            sf::RectangleShape rect;
            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1);

            double width = unit->data()->OutlineSize.x * Constants::TILE_SIZE_HORIZONTAL;
            double height =  unit->data()->OutlineSize.y * Constants::TILE_SIZE_VERTICAL;

            if (unit->data()->ObstructionType == genie::Unit::UnitObstruction) {
                width /= 2.;
                height /= 2.;
            } else {
                circle.setPointCount(4);
            }

            ScreenPos pos = camera->absoluteScreenPos(unit->position());

            circle.setPosition(pos.x - width, pos.y - height);
            circle.setRadius(width);
            circle.setScale(1, height / width);
            renderTarget->draw(circle);

            circle.setPosition(pos.x - width, pos.y - height + 1);
            circle.setOutlineColor(sf::Color::Black);
            renderTarget->draw(circle);

            pos.x -= Constants::TILE_SIZE_HORIZONTAL / 8;
            pos.y -= height + Constants::TILE_SIZE_HEIGHT * unit->data()->HPBarHeight;

            rect.setOutlineColor(sf::Color::Transparent);
            rect.setPosition(pos);

            if (unit->creationProgress() < 1.) {
                rect.setFillColor(sf::Color::Red);
                rect.setSize(sf::Vector2f(Constants::TILE_SIZE_HORIZONTAL / 4., 2));
                m_outlineOverlay.draw(rect);
            }

            rect.setFillColor(sf::Color::Green);
            rect.setSize(sf::Vector2f(unit->creationProgress() * Constants::TILE_SIZE_HORIZONTAL / 4., 2));
            m_outlineOverlay.draw(rect);
        }

        if (!(unit->data()->OcclusionMode & genie::Unit::ShowOutline)) {
            continue;
        }

        const ScreenPos pos = renderTarget->camera()->absoluteScreenPos(unit->position());
        unit->renderer().render(*renderTarget->renderTarget_,
                                pos,
                                RenderType::Base);

        unit->renderer().render(m_outlineOverlay, pos, RenderType::Outline);
    }

    m_outlineOverlay.display();
    renderTarget->draw(m_outlineOverlay.getTexture(), ScreenPos(0, 0));

#ifdef DEBUG
    for (const Unit::Ptr &unit : m_units) {
        if (!unit->isVisible) {
            continue;
        }
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

    if (m_buildingToPlace) {
        m_buildingToPlace->renderer().render(*renderTarget->renderTarget_,
                                             renderTarget->camera()->absoluteScreenPos(m_buildingToPlace->position()),
                                             RenderType::ConstructAvailable);
    }
}

bool UnitManager::onLeftClick(const MapPos &/*mapPos*/)
{
    if (m_buildingToPlace) {
        m_buildingToPlace->isVisible = true;
        m_buildingToPlace->setCreationProgress(0);
        m_units.insert(m_buildingToPlace);

        for (const Unit::Ptr &unit : m_selectedUnits) {
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

            unit->clearActionQueue();
            assignTask(task, unit, m_buildingToPlace);
        }

        m_buildingToPlace.reset();
        return true;
    }

    return false;
}

void UnitManager::onRightClick(const ScreenPos &screenPos, const CameraPtr &camera)
{
    if (m_selectedUnits.empty()) {
        return;
    }

    const Task task = defaultActionAt(screenPos, camera);
    if (task.data) {
        for (const Unit::Ptr &unit : m_selectedUnits) {
            unit->clearActionQueue();
            assignTask(task, unit, unitAt(screenPos, camera));
        }

        return;
    }


    const MapPos mapPos = camera->absoluteMapPos(screenPos);
    for (const Unit::Ptr &unit : m_selectedUnits) {
        moveUnitTo(unit, mapPos);
    }

    m_moveTargetMarker->moveTo(mapPos);
}

void UnitManager::onMouseMove(const MapPos &mapPos)
{
    if (m_buildingToPlace) {
        m_buildingToPlace->setPosition(mapPos);
        m_buildingToPlace->snapPositionToGrid();
    }
}

void UnitManager::selectUnits(const ScreenRect &selectionRect, const CameraPtr &camera)
{
    if (m_buildingToPlace) {
        return;
    }

    m_selectedUnits.clear();
    m_currentActions.clear();

    std::vector<Unit::Ptr> containedUnits;
    int8_t requiredInteraction = genie::Unit::ObjectInteraction;
    for (const Unit::Ptr &unit : m_units) {
        if (!selectionRect.overlaps(unit->rect() + camera->absoluteScreenPos(unit->position()))) {
            continue;
        }

        for (const genie::Resource<float, int8_t> &p : unit->data()->ResourceStorages) {
            DBG << p.Amount << p.Type << p.Flag;
        }

        requiredInteraction = std::max(unit->data()->InteractionMode, requiredInteraction);
        containedUnits.push_back(unit);
    }

    for (const Unit::Ptr &unit : containedUnits) {
        if (unit->data()->InteractionMode < requiredInteraction) {
            continue;
        }

        m_selectedUnits.insert(unit);
        m_currentActions.merge(unit->availableActions());

    }
    for (const Unit::Ptr &unit : m_selectedUnits) {
        // stl is shit
        for (std::unordered_set<Task>::iterator it = m_currentActions.begin(); it != m_currentActions.end();) {
            if (unit->availableActions().count(*it) == 0) {
                it = m_currentActions.erase(it);
            } else {
                it++;
            }
        }
    }

    if (m_selectedUnits.empty()) {
        DBG << "Unable to find anything to select in " << selectionRect;
    }

    if (m_selectedUnits.size() == 1) {
        playSound(*m_selectedUnits.begin());
    }
}

void UnitManager::setMap(const MapPtr &map)
{
    m_map = map;
}

void UnitManager::setSelectedUnits(const UnitSet &units)
{
    m_selectedUnits = units;
    m_buildingToPlace.reset();
}

void UnitManager::placeBuilding(const int unitId, const std::shared_ptr<Player> &player)
{
    m_buildingToPlace = UnitFactory::Inst().createUnit(unitId, MapPos(), player, m_map);
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

const Task UnitManager::defaultActionAt(const ScreenPos &pos, const CameraPtr &camera)
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

    int ownPlayerId = (*m_selectedUnits.begin())->playerId;

    for (const Task &task : m_currentActions) {
        const genie::Task *action = task.data;

        switch (action->TargetDiplomacy) {
        case genie::Task::TargetSelf:
            if (target->playerId != ownPlayerId) {
                continue;
            }
            break;
        case genie::Task::TargetNeutralsEnemies: // TODO: neutrals
            if (target->playerId == ownPlayerId) {
                continue;
            }
            break;

        case genie::Task::TargetGaiaOnly:
            if (target->playerId != 0) {
                continue;
            }
            break;
        case genie::Task::TargetSelfAllyGaia: // TODO: Allies
            if (target->playerId != ownPlayerId && target->playerId != 0) {
                continue;
            }
            break;
        case genie::Task::TargetGaiaNeutralEnemies:
        case genie::Task::TargetOthers:
            if (target->playerId == ownPlayerId) { // TODO: allies
                continue;
            }
            break;
        case genie::Task::TargetAnyDiplo:
        case genie::Task::TargetAnyDiplo2:
        default:
            break;
        }

        if (action->ActionType == genie::Task::Garrison) {
            continue;
        }

        if (action->ActionType == genie::Task::Combat &&
                action->TargetDiplomacy == genie::Task::TargetGaiaNeutralEnemies && ownPlayerId != target->playerId) {
            return task;
        }
        if (target->creationProgress() < 1) {
            if (action->ActionType == genie::Task::Build) {
                return task;
            }

            continue;
        }

        if (action->UnitID == target->data()->ID) {
            return task;
        }

        if (action->ClassID == target->data()->Class) {
            return task;
        }
    }

    return Task();
}

void UnitManager::moveUnitTo(const Unit::Ptr &unit, const MapPos &targetPos)
{
    unit->setCurrentAction(MoveOnMap::moveUnitTo(unit, targetPos, m_map, this));
}

void UnitManager::updateVisibility(const CameraPtr &camera)
{
    for (const Unit::Ptr &unit : m_units) {
        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position());
        const ScreenRect unitRect = unit->renderer().rect() + unitPosition;
        unit->isVisible = camera->isVisible(unitRect);

        for (Unit::Annex &annex : unit->annexes) {
            const ScreenPos annexPosition = camera->absoluteScreenPos(unit->position() + annex.offset);
            ScreenRect annexRect = annex.unit->renderer().rect() + annexPosition;
            annex.unit->isVisible = camera->isVisible(annexRect);
        }
    }
}

void UnitManager::assignTask(const Task &task, const Unit::Ptr &unit, const Unit::Ptr &target)
{
    if (!task.data) {
        WARN << "no task data";
        return;
    }

    if (task.unitId != unit->data()->ID) {
        unit->setUnitData(DataManager::Inst().getUnit(task.unitId));
    }

    unit->queueAction(MoveOnMap::moveUnitTo(unit, target->position(), m_map, this));
    switch(task.data->ActionType) {
    case genie::Task::Build:
        unit->queueAction(std::make_shared<ActionBuild>(unit, target));
        break;
    case genie::Task::GatherRebuild:
//        DBG << "supposed to gather from" << target->debugName;
        unit->queueAction(std::make_shared<ActionGather>(unit, target, task.data, this));
        break;
    default:
        return;
    }

}

void UnitManager::playSound(const Unit::Ptr &unit)
{
    const int id = unit->data()->SelectionSound;
    if (id < 0) {
        DBG << "no selection sound for" << unit->debugName;
        return;
    }

    AudioPlayer::instance().playSound(id, unit->civilization->id());
}
