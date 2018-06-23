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
#include <genie/dat/Unit.h>

Entity::Entity(const Entity::Type type_, const std::string &name) :
    type(type_),
    readableName(name)
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

Unit::Unit(const genie::Unit &data_, int playerId_, std::shared_ptr<Civilization> civilization) :
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    data(data_),
    playerId(playerId_),
    m_civilization(civilization)
{
    defaultGraphics = ResourceManager::Inst()->getGraphic(data.StandingGraphic.first),
    movingGraphics = ResourceManager::Inst()->getGraphic(data.Moving.WalkingGraphic);
    if (!defaultGraphics) {
        std::cerr << "Failed to load default graphics" << std::endl;
    }

    m_creationProgress = data.Creatable.TrainTime;

    m_graphics.setGraphic(defaultGraphics);
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

const std::vector<const genie::Unit *> Unit::creatableUnits()
{
    return m_civilization->creatableUnits(data.ID);
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
    if (data.Type == genie::Unit::BuildingType) {
        if (m_creationProgress < data.Creatable.TrainTime && progress >= data.Creatable.TrainTime) {
            m_graphics.setGraphic(defaultGraphics);
        } else if (m_creationProgress == data.Creatable.TrainTime && progress < data.Creatable.TrainTime) {
            m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(data.Building.ConstructionGraphicID));
        }
    }

    m_creationProgress = std::min(progress, float(data.Creatable.TrainTime));

    if (data.Type == genie::Unit::BuildingType && progress < data.Creatable.TrainTime) {
        m_graphics.setAngle(M_PI_2 + 2. * M_PI * (creationProgress()));
    }
}

void Unit::increaseCreationProgress(float progress)
{
    setCreationProgress(m_creationProgress + progress);
}

float Unit::creationProgress() const
{
    return m_creationProgress / float(data.Creatable.TrainTime);
}

std::unordered_set<const genie::Task *> Unit::availableActions()
{
    std::unordered_set<const genie::Task *> tasks;
    for (const genie::Task &task : DataManager::datFile().UnitHeaders[data.ID].TaskList) {
        tasks.insert(&task);
    }

    if (!data.Action.TaskSwapGroup) {
        return tasks;
    }

    for (const genie::Unit *swappable : m_civilization->swappableUnits(data.Action.TaskSwapGroup)) {
        for (const genie::Task &task : DataManager::datFile().UnitHeaders[swappable->ID].TaskList) {
            tasks.insert(&task);
        }
    }

    return tasks;
}

int Unit::taskGraphicId(const genie::Task::ActionTypes taskType, const Unit::State state)
{
    for (const genie::Task &task : DataManager::datFile().UnitHeaders[data.ID].TaskList) {
        if (task.ActionType != taskType) {
            continue;
        }

        switch(state) {
        case Idle:
        case Proceeding:
            return task.ProceedingGraphicID;
        case Moving:
            return task.MovingGraphicID;
        case Working:
            return task.ProceedingGraphicID;
            return task.WorkingGraphicID;
        case Carrying:
            return task.CarryingGraphicID;
        default:
            return data.StandingGraphic.first;
        }
    }

    return data.StandingGraphic.first;
}

void Unit::setAngle(const float angle)
{
    m_graphics.setAngle(angle);
}

void Unit::queueAction(ActionPtr action)
{
    if (!m_currentAction) {
        m_currentAction = action;
    } else {
        m_actionQueue.push_back(action);

    }
}

void Unit::setCurrentAction(ActionPtr action)
{
    m_currentAction = action;

    if (!action) {
        return;
    }

    if (action->type == IAction::Type::Move) {
        m_graphics.setGraphic(movingGraphics);
    } else if (action->type == IAction::Type::Build) {
        m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(taskGraphicId(genie::Task::Build, Working)));
        std::cout << m_graphics.graphic_->data_.AngleCount << " " << m_graphics.graphic_->data_.FrameCount << std::endl;
    } else {
        m_graphics.setGraphic(defaultGraphics);
    }
}

void Unit::removeAction(IAction *action)
{
    if (m_currentAction.get() == action) {
        m_currentAction.reset();
        m_graphics.setGraphic(defaultGraphics);

        if (!m_actionQueue.empty()) {
            std::cout << "changing action to queued one" << std::endl;
            setCurrentAction(m_actionQueue.front());
            m_actionQueue.pop_front();
        } else {
            std::cout << "no actions queued" << std::endl;
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
}

MoveTargetMarker::MoveTargetMarker() :
    Entity(Type::MoveTargetMarker, "Move target marker")
{
    m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(2961));

    m_graphics.current_frame_ = m_graphics.graphic_->data_.FrameCount - 1; // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos)
{
    position = pos;
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
