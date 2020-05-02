#include "ActionGarrison.h"
#include "ActionMove.h"

#include "mechanics/Building.h"
#include "mechanics/Unit.h"

#include "global/EventManager.h"

#include <genie/dat/Unit.h>

ActionGarrison::ActionGarrison(const std::shared_ptr<Unit> &unit, const Task &task) :
    IAction(Type::Garrison, unit, task),
    m_target(Unit::asBuilding(task.target))
{
}

IAction::UpdateResult ActionGarrison::update(Time /*time*/)
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "impossible, lost own unit";
        return UpdateResult::Failed;
    }
    Building::Ptr target = m_target.lock();
    if (!unit) {
        WARN << "garrison target lost";
        return UpdateResult::Failed;
    }

    if (target->data()->GarrisonCapacity <= 0) {
        WARN << "Building has no garrison capacity";
        return UpdateResult::Failed;
    }

    if (unit->distanceTo(target) > 1.) { // idk lol
        DBG << "Out of range, moving closer";
        unit->actions.prependAction(ActionMove::moveUnitTo(unit, target));
        return UpdateResult::Updated;
    }

    if (target->garrisonedUnits.size() >= target->data()->GarrisonCapacity) {
        WARN << "Building full, can't garrison";
        return UpdateResult::Failed;
    }

    target->garrisonedUnits.push_back(unit);
    unit->garrisonedIn = target;

    EventManager::unitGarrisoned(unit.get(), target.get());

    return UpdateResult::Completed;
}
