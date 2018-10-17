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

#include "Unit.h"
#include "resource/LanguageManager.h"
#include "mechanics/Civilization.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"
#include "global/Constants.h"
#include "resource/DataManager.h"
#include <genie/dat/Unit.h>
#include "core/Utility.h"

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, const std::shared_ptr<Civilization> &civilization_, const MapPtr &map) :
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")", map),
    playerId(player_->playerId),
    player(player_),
    civilization(civilization_)
{
    setUnitData(data_);

    m_creationProgress = m_data->Creatable.TrainTime;
    hitPoints = m_data->HitPoints;
}

Unit::~Unit()
{
}

bool Unit::update(Time time)
{
    bool updated = false;

    for (Annex &annex : annexes) {
        updated = annex.unit->update(time) || updated;
    }

    if (m_currentAction) {
        switch(m_currentAction->update(time)) {
        case IAction::UpdateResult::Completed:
            removeAction(m_currentAction);
            break;
        case IAction::UpdateResult::Updated:
            updated = true;
            break;
        case IAction::UpdateResult::NotUpdated:
            break;
        }
    }


    return Entity::update(time) || updated;
}

void Unit::snapPositionToGrid()
{
    MapPos newPos = position();
    newPos /= Constants::TILE_SIZE;
    newPos += Size(m_data->Size);
    newPos.round();
    newPos -= Size(m_data->Size);
    newPos *= Constants::TILE_SIZE;

    setPosition(newPos);
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
    ScreenRect ret = m_renderer.rect();

    for (const Annex &annex : annexes) {
        ret += annex.unit->rect();
    }

    return ret;
}

void Unit::setCreationProgress(float progress)
{
    if (m_data->Type == genie::Unit::BuildingType) {
        if (m_creationProgress < m_data->Creatable.TrainTime && progress >= m_data->Creatable.TrainTime) {
            m_renderer.setGraphic(defaultGraphics);
        } else if (m_creationProgress == m_data->Creatable.TrainTime && progress < m_data->Creatable.TrainTime) {
            m_renderer.setGraphic(AssetManager::Inst()->getGraphic(m_data->Building.ConstructionGraphicID));
        }
    }

    m_creationProgress = std::min(progress, float(m_data->Creatable.TrainTime));

    if (m_data->Type == genie::Unit::BuildingType && progress < m_data->Creatable.TrainTime) {
        m_renderer.setAngle(M_PI_2 + 2. * M_PI * (creationProgress()));
    }
}

void Unit::increaseCreationProgress(float progress)
{
    setCreationProgress(m_creationProgress + progress);
}

float Unit::creationProgress() const
{
    if (IS_UNLIKELY(m_data->Creatable.TrainTime == 0)) {
        return 0;
    }

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

    defaultGraphics = AssetManager::Inst()->getGraphic(m_data->StandingGraphic.first);
    if (m_data->Moving.WalkingGraphic >= 0) {
        movingGraphics = AssetManager::Inst()->getGraphic(m_data->Moving.WalkingGraphic);
    }

    if (!defaultGraphics) {
        WARN << "Failed to load default graphics";
    }

    m_renderer.setGraphic(defaultGraphics);
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
    m_renderer.setAngle(angle);
}

void Unit::queueAction(const ActionPtr &action)
{
    if (!m_currentAction) {
        setCurrentAction(action);
    } else {
        m_actionQueue.push_back(action);

    }
}

void Unit::setCurrentAction(const ActionPtr &action)
{
    if (m_currentAction && !action) {
        m_renderer.setGraphic(defaultGraphics);
    }

    m_currentAction = action;

    if (!action) {
        return;
    }

    switch (action->type) {
    case IAction::Type::Move:
        m_renderer.setGraphic(movingGraphics);
        break;
    case IAction::Type::Build:
        m_renderer.setGraphic(AssetManager::Inst()->getGraphic(taskGraphicId(genie::Task::Build, action->unitState())));
        break;
    case IAction::Type::Gather:
        m_renderer.setGraphic(AssetManager::Inst()->getGraphic(taskGraphicId(genie::Task::GatherRebuild, action->unitState())));
        break;
    default:
        m_renderer.setGraphic(defaultGraphics);
    }
}

void Unit::removeAction(const ActionPtr &action)
{
    if (action == m_currentAction) {
        m_currentAction.reset();
        m_renderer.setGraphic(defaultGraphics);

        if (!m_actionQueue.empty()) {
            DBG << "changing action to queued one";
            setCurrentAction(m_actionQueue.front());
            m_actionQueue.pop_front();
        } else {
            DBG << "no actions queued";
        }
    } else {
        // fuck stl
        std::deque<ActionPtr>::iterator it = std::find(m_actionQueue.begin(), m_actionQueue.end(), action);

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
