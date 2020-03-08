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

#include "IAction.h"

#include <genie/dat/Unit.h>
#include <genie/dat/UnitCommand.h>
#include <memory>
#include <unordered_set>

#include "ActionAttack.h"
#include "ActionBuild.h"
#include "ActionGather.h"
#include "ActionMove.h"
#include "actions/IAction.h"
#include "core/Logger.h"
#include "global/EventManager.h"
#include "mechanics/Player.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"

IAction::IAction(const Type type_, const std::shared_ptr<Unit> &unit, const Task &task) :
    type(type_),
    m_unit(unit),
    m_task(task)
{
}

void IAction::assignTask(const Task &task, const std::shared_ptr<Unit> &unit, const std::shared_ptr<Unit> &target)
{
    if (!task.data) {
        WARN << "no task data";
        return;
    }

    switch(task.data->ActionType) {
    case genie::ActionType::Build: {
        if (!target) {
            DBG << "Can't build nothing";
            return;
        }

        unit->actions.queueAction(ActionMove::moveUnitTo(unit, target->position(), task));

        ActionPtr buildAction = std::make_shared<ActionBuild>(unit, target, task);
        buildAction->requiredUnitID = task.unitId;
        unit->actions.queueAction(buildAction);

        if (target->data()->Class == genie::Unit::Farm) {
            Task farmTask = unit->actions.findAnyTask(genie::ActionType::GatherRebuild, target->data()->ID);
            ActionPtr farmAction = std::make_shared<ActionGather>(unit, target, farmTask);
            farmAction->requiredUnitID = farmTask.unitId;
            unit->actions.queueAction(farmAction);
        }
        break;
    }
    case genie::ActionType::Hunt:
    case genie::ActionType::GatherRebuild: {
        if (!target) {
            DBG << "Can't gather from nothing";
            return;
        }
        unit->actions.queueAction(ActionMove::moveUnitTo(unit, target->position(), task));
        ActionPtr farmAction = std::make_shared<ActionGather>(unit, target, task);
        farmAction->requiredUnitID = task.unitId;
        unit->actions.queueAction(farmAction);
        break;
    }
    case genie::ActionType::Combat: {
        if (target) {
            DBG << "attacking" << target->debugName;
        }

        ActionPtr combatAction = std::make_shared<ActionAttack>(unit, target, task);
        combatAction->requiredUnitID = task.unitId;
        unit->actions.queueAction(combatAction);
        break;
    }
    default:
        return;
    }

    if (target) {
        EventManager::unitGotTarget(unit.get(), target.get());
    }
}

IAction::~IAction()
{
}

Task::Task(const genie::Task &t, int id) : taskId(t.ID), data(&t), unitId(id) {}

bool Task::operator==(const Task &other) const
{
    return unitId == other.unitId && (
                (data && other.data && data->ID == other.data->ID) ||
                (data == other.data)
                );
}
