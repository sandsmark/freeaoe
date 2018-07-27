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
#include "Entity.h"
#include "resource/DataManager.h"

IAction::IAction(const Type type_) :
    type(type_)
{
}

IAction::~IAction()
{
}

void IAction::assignTask(const Task &task, const std::shared_ptr<Unit> &unit, const std::shared_ptr<Unit> &target)
{
    if (!task.data) {
        WARN << "no task data";
        return;
    }

    if (task.unitId != unit->data()->ID) {
        unit->setUnitData(DataManager::Inst().getUnit(task.unitId));
    }

    switch(task.data->ActionType) {
    case genie::Task::GatherRebuild:
        DBG << "supposed to gather from" << target->debugName;
        break;
    default:
        return;
    }
}
