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
#include "mechanics/Entity.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Civilization.h"
#include "resource/DataManager.h"
#include "audio/AudioPlayer.h"

#include "ActionAttack.h"
#include "ActionMove.h"
#include "ActionBuild.h"
#include "ActionGather.h"

IAction::IAction(const Type type_, const std::shared_ptr<Unit> &unit, UnitManager *unitManager) :
    type(type_),
    m_unit(unit),
    m_unitManager(unitManager)
{
}

Task IAction::findMatchingTask(const int ownPlayerId, const std::shared_ptr<Unit> &target, const std::unordered_set<Task> &potentials)
{
    for (const Task &task : potentials) {
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
            if (target->playerId != UnitManager::GaiaID) {
                continue;
            }
            break;
        case genie::Task::TargetSelfAllyGaia: // TODO: Allies
            if (target->playerId != ownPlayerId && target->playerId != UnitManager::GaiaID) {
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

    // Try more generic targeting
    for (const Task &task : potentials) {
        const genie::Task *action = task.data;
        if (action->ActionType != genie::Task::Combat) {
            continue;
        }
        if (action->TargetDiplomacy != genie::Task::TargetGaiaNeutralEnemies && action->TargetDiplomacy != genie::Task::TargetNeutralsEnemies) {
            continue;
        }
        if (ownPlayerId == target->playerId) {
            continue;
        }

        if (target->data()->Type < genie::Unit::CombatantType) {
            continue;
        }

        return task;
    }

    return Task();

}

void IAction::assignTask(const Task &task, const std::shared_ptr<Unit> &unit, const std::shared_ptr<Unit> &target)
{
    if (!task.data) {
        WARN << "no task data";
        return;
    }

    switch(task.data->ActionType) {
    case genie::Task::Build: {
        if (!target) {
            DBG << "Can't build nothing";
            return;
        }

        unit->queueAction(ActionMove::moveUnitTo(unit, target->position(), unit->map(), &unit->unitManager()));

        ActionPtr buildAction = std::make_shared<ActionBuild>(unit, target, &unit->unitManager());
        buildAction->requiredUnitID = task.unitId;
        unit->queueAction(buildAction);

        if (target->data()->Class == genie::Unit::Farm) {
            Task farmTask = unit->findMatchingTask(genie::Task::GatherRebuild, target->data()->ID);
            ActionPtr farmAction = std::make_shared<ActionGather>(unit, target, farmTask.data, &unit->unitManager());
            farmAction->requiredUnitID = farmTask.unitId;
            unit->queueAction(farmAction);
        }
        break;
    }
    case genie::Task::Hunt:
    case genie::Task::GatherRebuild: {
        if (!target) {
            DBG << "Can't gather from nothing";
            return;
        }
        unit->queueAction(ActionMove::moveUnitTo(unit, target->position(), unit->map(), &unit->unitManager()));
        ActionPtr farmAction = std::make_shared<ActionGather>(unit, target, task.data, &unit->unitManager());
        farmAction->requiredUnitID = task.unitId;
        unit->queueAction(farmAction);
        break;
    }
    case genie::Task::Combat: {
        if (target) {
            DBG << "attacking" << target->debugName;
        }

        AudioPlayer::instance().playSound(unit->data()->Action.AttackSound, unit->civilization->id());
        ActionPtr combatAction = std::make_shared<ActionAttack>(unit, target, &unit->unitManager());
        combatAction->requiredUnitID = task.unitId;
        unit->queueAction(combatAction);
        break;
    }
    default:
        return;
    }

}

IAction::~IAction()
{
}
