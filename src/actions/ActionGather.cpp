#include "ActionGather.h"

#include "IAction.h"
#include "ActionAttack.h"
#include "ActionMove.h"
#include "core/Logger.h"
#include "core/ResourceMap.h"
#include "mechanics/Player.h"
#include "mechanics/UnitManager.h"

#include <genie/dat/Unit.h>
#include <genie/dat/UnitCommand.h>
#include <genie/dat/unit/Action.h>
#include <algorithm>
#include <limits>
#include <utility>

ActionGather::ActionGather(const std::shared_ptr<Unit> &unit, const std::shared_ptr<Unit> &target, const Task &task) :
    IAction(Type::Gather, unit, task),
    m_target(target)
{
    m_resourceType = genie::ResourceType(m_task.data->ResourceIn);
    DBG << unit->debugName << "gathering from" << target->debugName;

    if (m_task.data->ResourceOut >= 0 && m_task.data->ResourceOut < int(genie::ResourceType::NumberOfTypes)) {
        m_resourceType = genie::ResourceType(m_task.data->ResourceOut);
    }
}

IAction::UpdateResult ActionGather::update(Time time)
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "Missed my own unit";
        return UpdateResult::Completed;
    }

    Unit::Ptr target = m_target.lock();
    if (!target) {
        WARN << "target gone";
        if (unit->resources[m_resourceType] == 0) {
            return UpdateResult::Completed;
        }
        const Unit::Ptr dropSite = findDropSite(unit);
        if (!dropSite) {
            WARN << "Couldn't even find a drop site!";
            return UpdateResult::Completed;
        }

        DBG << "moving to" << dropSite->position() << "to drop off, then returning to" << unit->position();

        // Bleh, will be fucked if there's more in the queue, but I'm lazy
        unit->actions.queueAction(ActionMove::moveUnitTo(unit, dropSite->position(), m_task));
        unit->actions.queueAction(std::make_shared<ActionDropOff>(unit, dropSite, m_task));
        unit->actions.queueAction(ActionMove::moveUnitTo(unit, unit->position(), m_task));

        return UpdateResult::Completed;
    }


    if (target->healthLeft() > 0 && target->playerId != unit->playerId) {
        DBG << "Unit isn't dead, attacking first";
        unit->actions.prependAction(std::make_shared<ActionAttack>(unit, target, m_task));
        return UpdateResult::NotUpdated;
    }

    if (!m_prevTime) {
        ScreenPos screenPosition = unit->position().toScreen();
        ScreenPos targetScreenPosition = target->position().toScreen();
        unit->setAngle(screenPosition.angleTo(targetScreenPosition));

        m_prevTime = time;
        return UpdateResult::NotUpdated;
    }

    if (unit->resources[m_resourceType] >= unit->data()->ResourceCapacity || target->resources[m_resourceType] == 0) {
        if (target->resources[m_resourceType] == 0) {
            DBG << target->debugName << "is empty" << target->resources[m_resourceType];
        } else {
            DBG << unit->debugName << "is full" << unit->resources[m_resourceType] << "/" << unit->data()->ResourceCapacity;
        }

        const MapPos &currentPos = unit->position();

        const Unit::Ptr dropSite = findDropSite(unit);

        if (dropSite) {
            DBG << "moving to" << dropSite->position() << "to drop off, then returning to" << currentPos << "to continue gathering";

            unit->actions.queueAction(ActionMove::moveUnitTo(unit, dropSite->position(), m_task));
            unit->actions.queueAction(std::make_shared<ActionDropOff>(unit, dropSite, m_task));
            unit->actions.queueAction(ActionMove::moveUnitTo(unit, currentPos, m_task));

            if (target->resources[m_resourceType] > 0) {
                unit->actions.queueAction(std::make_shared<ActionGather>(unit, target, m_task));
            }
        } else {
            WARN << "failed to find a drop site";
        }

        return UpdateResult::Completed;
    }


    float amount = unit->data()->Action.WorkRate * m_task.data->WorkValue1;
    if (m_task.data->ResourceMultiplier >= 0) {
        Player::Ptr player = unit->player.lock();
        if (!player) {
            WARN << "player gone";
            return UpdateResult::Completed;
        }

        amount *= player->resourcesAvailable(genie::ResourceType(m_task.data->ResourceMultiplier));
    }

    amount *= (time - m_prevTime) * 0.0015;
    m_prevTime = time;

    amount = std::min(amount, target->resources[m_resourceType]);

    target->resources[m_resourceType] -= amount;
    unit->resources[m_resourceType] += amount;

    return UpdateResult::Updated;
}

IAction::UnitState ActionGather::unitState() const
{
    if (m_task.data->ActionType == genie::ActionType::Hunt) {
        return UnitState::Working;
    } else {
        return UnitState::Proceeding;
    }
}

genie::ActionType ActionGather::taskType() const
{
    return m_task.data->ActionType;
}

std::shared_ptr<Unit> ActionGather::findDropSite(const std::shared_ptr<Unit> &unit)
{
    float closestDistance = std::numeric_limits<float>::max();
    MapPos closestPos = unit->position(); // fallback
    Unit::Ptr closestUnit;

    const int dropUnitId1 = unit->data()->Action.DropSite.first;
    const int dropUnitId2 = unit->data()->Action.DropSite.second;

    for (const Unit::Ptr &other : unit->unitManager().units()) {
        if (other->data()->ID != dropUnitId1 && other->data()->ID != dropUnitId2) {
            continue;
        }

        const float distance = unit->position().distance(other->position());
        if (distance > closestDistance) {
            continue;
        }

        closestDistance = distance;
        closestPos = other->position();
        closestUnit = other;
    }

    return closestUnit;
}


ActionDropOff::ActionDropOff(const std::shared_ptr<Unit> &unit, const std::shared_ptr<Unit> &target, const Task &task) :
    IAction(Type::DropOff, unit, task),
    m_target(target)
{
    m_resourceType = genie::ResourceType(m_task.data->ResourceIn);
    DBG << unit->debugName << "dropping off" << target->debugName;

    if (m_task.data->ResourceOut >= 0 && m_task.data->ResourceOut < int(genie::ResourceType::NumberOfTypes)) {
        m_resourceType = genie::ResourceType(m_task.data->ResourceOut);
    }
}

IAction::UpdateResult ActionDropOff::update(Time /*time*/)
{
    // TODO check if we need to move closer

    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "Unit gone";
        return UpdateResult::Completed;
    }

    Unit::Ptr target = m_target.lock();
    if (!target) {
        WARN << "target gone";
        return UpdateResult::Completed;
    }

    Player::Ptr targetPlayer = target->player.lock();
    if (!targetPlayer) {
        WARN << "player gone";
        return UpdateResult::Completed;
    }

    DBG << "dropping off" << unit->resources[m_resourceType] << "resource of type" << m_resourceType;

    targetPlayer->addResource(m_resourceType, unit->resources[m_resourceType]);
    unit->resources[m_resourceType] = 0;

    return UpdateResult::Completed;
}

genie::ActionType ActionDropOff::taskType() const
{
    return m_task.data->ActionType;
}
