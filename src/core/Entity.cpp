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

#include "global/Constants.h"
#include "Entity.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "render/GraphicRender.h"
#include "mechanics/Civilization.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"
#include <genie/dat/Unit.h>

static size_t s_entityCount = 0;

Entity::Entity(const Entity::Type type_, const std::string &name) :
    id(s_entityCount++),
    type(type_),
    debugName(name)
{
}

Entity::~Entity()
{
}

bool Entity::update(Time time)
{
    bool updated = false;

    updated = m_graphics.update(time) || updated;

    return updated && isVisible;
}

std::shared_ptr<Unit> Entity::asUnit(EntityPtr entity)
{
    if (!entity) {
        return nullptr;
    }

    if (entity->type != Type::Unit) {
        return nullptr;
    }
    return std::static_pointer_cast<Unit>(entity);
}

void Entity::setPosition(const MapPos &pos, const MapPtr &map)
{
    if (!map) {
        WARN << "No map passed";
        return;
    }

    int oldTileX = m_position.x / Constants::TILE_SIZE;
    int oldTileY = m_position.y / Constants::TILE_SIZE;
    int newTileX = pos.x / Constants::TILE_SIZE;
    int newTileY = pos.y / Constants::TILE_SIZE;

    m_position = pos;
    if (newTileX == oldTileX && newTileY == oldTileY) {
        return;
    }

    map->removeEntityAt(oldTileX, oldTileY, shared_from_this());
    map->addEntityAt(newTileX, newTileY, shared_from_this());
}

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, std::shared_ptr<Civilization> civilization_) :
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    playerId(player_->playerId),
    player(player_),
    civilization(civilization_)
{
    setUnitData(data_);

    m_creationProgress = m_data->Creatable.TrainTime;
}

bool Unit::update(Time time)
{
    bool updated = false;

    for (Annex &annex : annexes) {
        updated = annex.unit->update(time) || updated;
    }

    if (m_currentAction) {
        updated = m_currentAction->update(time) || updated;
    }


    return Entity::update(time) || updated;
}

void Unit::snapPositionToGrid(const MapPtr &map)
{
    MapPos newPos = position();
    newPos /= Constants::TILE_SIZE;
    newPos += Size(m_data->Size);
    newPos.round();
    newPos -= Size(m_data->Size);
    newPos *= Constants::TILE_SIZE;

    setPosition(newPos, map);
}

const std::vector<const genie::Unit *> Unit::creatableUnits()
{
    if (creationProgress() < 1.) {
        return {};
    }

    return civilization->creatableUnits(m_data->ID);
}

ScreenRect Unit::rect() const
{
    ScreenRect ret = m_graphics.rect();

    for (const Annex &annex : annexes) {
        ret += annex.unit->rect();
    }

    return ret;
}

void Unit::setCreationProgress(float progress)
{
    if (m_data->Type == genie::Unit::BuildingType) {
        if (m_creationProgress < m_data->Creatable.TrainTime && progress >= m_data->Creatable.TrainTime) {
            m_graphics.setGraphic(defaultGraphics);
        } else if (m_creationProgress == m_data->Creatable.TrainTime && progress < m_data->Creatable.TrainTime) {
            m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(m_data->Building.ConstructionGraphicID));
        }
    }

    m_creationProgress = std::min(progress, float(m_data->Creatable.TrainTime));

    if (m_data->Type == genie::Unit::BuildingType && progress < m_data->Creatable.TrainTime) {
        m_graphics.setAngle(M_PI_2 + 2. * M_PI * (creationProgress()));
    }
}

void Unit::increaseCreationProgress(float progress)
{
    setCreationProgress(m_creationProgress + progress);
}

float Unit::creationProgress() const
{
    return m_creationProgress / float(m_data->Creatable.TrainTime);
}

std::unordered_set<Task> Unit::availableActions()
{
    std::unordered_set<Task> tasks;
    for (const genie::Task &task : DataManager::datFile().UnitHeaders[m_data->ID].TaskList) {
        tasks.insert(Task(task, m_data->ID));
    }

    if (!m_data->Action.TaskSwapGroup) {
        return tasks;
    }

    for (const genie::Unit *swappable : civilization->swappableUnits(m_data->Action.TaskSwapGroup)) {
        for (const genie::Task &task : DataManager::datFile().UnitHeaders[swappable->ID].TaskList) {
            tasks.insert(Task(task, swappable->ID));
        }
    }

    return tasks;
}

void Unit::setUnitData(const genie::Unit &data_)
{
    m_data = &data_;
    DBG <<     (LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")");

    defaultGraphics = ResourceManager::Inst()->getGraphic(m_data->StandingGraphic.first);
    if (m_data->Moving.WalkingGraphic >= 0) {
        movingGraphics = ResourceManager::Inst()->getGraphic(m_data->Moving.WalkingGraphic);
    }

    if (!defaultGraphics) {
        WARN << "Failed to load default graphics";
    }

    m_graphics.setGraphic(defaultGraphics);

}

int Unit::taskGraphicId(const genie::Task::ActionTypes taskType, const IAction::UnitState state)
{
    for (const Task &task : availableActions()) {
        if (task.data->ActionType != taskType) {
            continue;
        }

        switch(state) {
        case IAction::Idle:
        case IAction::Proceeding:
            return task.data->ProceedingGraphicID;
        case IAction::Moving:
            return task.data->MovingGraphicID;
        case IAction::Working:
            return task.data->WorkingGraphicID;
        case IAction::Carrying:
            return task.data->CarryingGraphicID;
        default:
            return m_data->StandingGraphic.first;
        }
    }

    return m_data->StandingGraphic.first;
}

void Unit::setAngle(const float angle)
{
    m_graphics.setAngle(angle);
}

void Unit::queueAction(ActionPtr action)
{
    if (!m_currentAction) {
        setCurrentAction(action);
    } else {
        m_actionQueue.push_back(action);

    }
}

void Unit::setCurrentAction(ActionPtr action)
{
    if (m_currentAction && !action) {
        m_graphics.setGraphic(defaultGraphics);
    }

    m_currentAction = action;

    if (!action) {
        return;
    }

    switch (action->type) {
    case IAction::Type::Move:
        m_graphics.setGraphic(movingGraphics);
        break;
    case IAction::Type::Build:
        m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(taskGraphicId(genie::Task::Build, action->unitState())));
        break;
    case IAction::Type::Gather:
        m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(taskGraphicId(genie::Task::GatherRebuild, action->unitState())));
        break;
    default:
        m_graphics.setGraphic(defaultGraphics);
    }
}

void Unit::removeAction(IAction *action)
{
    if (m_currentAction.get() == action) {
        m_currentAction.reset();
        m_graphics.setGraphic(defaultGraphics);

        if (!m_actionQueue.empty()) {
            DBG << "changing action to queued one";
            setCurrentAction(m_actionQueue.front());
            m_actionQueue.pop_front();
        } else {
            DBG << "no actions queued";
        }
    } else {
        // fuck stl
        std::deque<ActionPtr>::iterator it = std::find_if(m_actionQueue.begin(), m_actionQueue.end(), [=](const ActionPtr &p) {
            return p.get() == action;
        });

        if (it != std::end(m_actionQueue)) {
            m_actionQueue.erase(it);
        }
    }
}

void Unit::clearActionQueue()
{
    m_actionQueue.clear();
    m_currentAction.reset();
}

MoveTargetMarker::MoveTargetMarker() :
    Entity(Type::MoveTargetMarker, "Move target marker")
{
    m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(2961));

    m_graphics.current_frame_ = m_graphics.graphic_->data_.FrameCount - 1; // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos)
{
    m_position = pos;
    m_graphics.current_frame_ = 0;
    m_isRunning = true;
}

bool MoveTargetMarker::update(Time time)
{
    if (!m_isRunning) {
        return false;
    }

    bool updated = Entity::update(time);

    if (m_graphics.current_frame_ >= m_graphics.graphic_->data_.FrameCount - 1) {
        m_isRunning = false;
    }

    return updated;
}
