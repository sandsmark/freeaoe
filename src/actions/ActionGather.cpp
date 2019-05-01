#include "ActionGather.h"
#include "ActionAttack.h"
#include "mechanics/Entity.h"
#include "mechanics/Player.h"
#include "ActionMove.h"
#include "mechanics/UnitManager.h"
#include <genie/dat/Unit.h>
#include <limits>

ActionGather::ActionGather(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task) :
    IAction(Type::Gather, unit),
    m_target(target),
    m_task(task)
{
    m_resourceType = genie::ResourceType(m_task->ResourceIn);
    DBG << unit->debugName << "gathering from" << target->debugName;

    if (m_task->ResourceOut >= 0 && m_task->ResourceOut < int(genie::ResourceType::NumberOfTypes)) {
        m_resourceType = genie::ResourceType(m_task->ResourceOut);
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
        unit->queueAction(ActionMove::moveUnitTo(unit, dropSite->position(), unit->map()));
        unit->queueAction(std::make_shared<ActionDropOff>(unit, dropSite, m_task));
        unit->queueAction(ActionMove::moveUnitTo(unit, unit->position(), unit->map()));

        return UpdateResult::Completed;
    }

    if (target->healthLeft() > 0 && target->playerId != unit->playerId) {
        DBG << "Unit isn't dead, attacking first";
        unit->prependAction(std::make_shared<ActionAttack>(unit, target));
        return UpdateResult::NotUpdated;
    }

    if (!m_prevTime) {
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

            unit->queueAction(ActionMove::moveUnitTo(unit, dropSite->position(), unit->map()));
            unit->queueAction(std::make_shared<ActionDropOff>(unit, dropSite, m_task));
            unit->queueAction(ActionMove::moveUnitTo(unit, currentPos, unit->map()));

            if (target->resources[m_resourceType] > 0) {
                unit->queueAction(std::make_shared<ActionGather>(unit, target, m_task));
            }
        } else {
            WARN << "failed to find a drop site";
        }

        return UpdateResult::Completed;
    }


    float amount = unit->data()->Action.WorkRate * m_task->WorkValue1;
    if (m_task->ResourceMultiplier >= 0) {
        Player::Ptr player = unit->player.lock();
        if (!player) {
            WARN << "player gone";
            return UpdateResult::Completed;
        }

        amount *= player->resourcesAvailable[genie::ResourceType(m_task->ResourceMultiplier)];
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
    if (m_task->ActionType == genie::Task::Hunt) {
        return UnitState::Working;
    } else {
        return UnitState::Proceeding;
    }
}

Unit::Ptr ActionGather::findDropSite(const Unit::Ptr &unit)
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


ActionDropOff::ActionDropOff(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task) :
    IAction(Type::DropOff, unit),
    m_target(target),
    m_task(task)
{
    m_resourceType = genie::ResourceType(m_task->ResourceIn);
    DBG << unit->debugName << "dropping off" << target->debugName;

    if (m_task->ResourceOut >= 0 && m_task->ResourceOut < int(genie::ResourceType::NumberOfTypes)) {
        m_resourceType = genie::ResourceType(m_task->ResourceOut);
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

    targetPlayer->resourcesAvailable[m_resourceType] += unit->resources[m_resourceType] ;
    unit->resources[m_resourceType] = 0;

    return UpdateResult::Completed;
}
