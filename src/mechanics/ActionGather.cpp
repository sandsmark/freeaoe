#include "ActionGather.h"
#include "core/Entity.h"
#include "mechanics/Player.h"
#include <genie/dat/Unit.h>

ActionGather::ActionGather(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task) : IAction(Type::Gather, unit),
    m_target(target),
    m_task(task)
{

}

bool ActionGather::update(Time time)
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "Unit gone";
        return true;
    }

    Unit::Ptr target = m_target.lock();
    if (!target) {
        WARN << "target gone";
        unit->removeAction(this);
        return true;
    }

    if (!m_prevTime) {
        m_prevTime = time;
        return false;
    }


    float amount = unit->data()->Action.WorkRate * m_task->WorkValue1;
    if (m_task->ResourceMultiplier >= 0) {
        Player::Ptr player = unit->player.lock();
        if (!player) {
            WARN << "player gone";
            return true;
        }

        amount *= player->resources[genie::ResourceType(m_task->ResourceMultiplier)];
    }

    amount *= (time - m_prevTime) * 0.0015;
    m_prevTime = time;

    genie::ResourceType inputResource = genie::ResourceType(m_task->ResourceIn);

    genie::ResourceType resourceType = inputResource;
    if (m_task->ResourceOut >= 0) {
        resourceType = genie::ResourceType(m_task->ResourceOut);
    }


    amount = std::min(amount, target->resources[resourceType]);
    target->resources[resourceType] -= amount;


    unit->resources[resourceType] += amount;

//    DBG << m_task->ResourceIn << m_task->ResourceOut << target->resources[inputResource] << unit->resources[resourceType];

    return false;
}

