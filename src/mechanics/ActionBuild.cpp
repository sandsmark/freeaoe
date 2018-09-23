#include "ActionBuild.h"

#include <genie/dat/Unit.h>

ActionBuild::ActionBuild(const Unit::Ptr &builder, const Unit::Ptr &building) : IAction(Type::Build, builder),
    m_targetBuilding(building)
{
}

ActionBuild::~ActionBuild()
{
    Unit::Ptr building = m_targetBuilding.lock();

    if (building && m_prevTime) {
        building->constructors--;
    }
}

IAction::UpdateResult ActionBuild::update(Time time)
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "Unit gone";
        return UpdateResult::Completed;
    }

    Unit::Ptr building = m_targetBuilding.lock();
    if (!building) {
        return UpdateResult::Completed;
    }

    if (!m_prevTime) {
        m_prevTime = time;
        building->constructors++;
        return UpdateResult::NotUpdated;
    }

    if (building->creationProgress() >= 1.) {
        return UpdateResult::Completed;
    }

    float progress = 3. / (building->constructors + 2.);
    progress *= (time - m_prevTime) * 0.0015;
    m_prevTime = time;

    building->increaseCreationProgress(progress);

    if (building->creationProgress() >= 1.) {
        DBG << "building finished";
        if (building->data()->Class == genie::Unit::Farm) {
//            unit->queueAction(std::make_shared<ActionGather>(unit, building, m_task, m_unitManager));
        }
        return UpdateResult::Completed;
    }

    return UpdateResult::Updated;
}

IAction::UnitState ActionBuild::unitState() const
{
    std::shared_ptr<Unit> target = m_targetBuilding.lock();
    if (!target) {
        WARN << "target lost";
        return Idle;
    }

    if (target->data()->ID == Unit::Farm) {
        return Working;
    }

    return Proceeding;
}
