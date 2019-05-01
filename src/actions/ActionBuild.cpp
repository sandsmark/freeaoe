#include "ActionBuild.h"
#include "ActionGather.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Building.h"

#include <genie/dat/Unit.h>

ActionBuild::ActionBuild(const Unit::Ptr &builder, const Unit::Ptr &building, const Task &task) :
    IAction(Type::Build, builder, task),
    m_targetBuilding(Unit::asBuilding(building))
{
    DBG << builder->debugName << "building" << building->debugName;
}

ActionBuild::~ActionBuild()
{
    Building::Ptr building = m_targetBuilding.lock();

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

    Building::Ptr building = m_targetBuilding.lock();
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
        return UpdateResult::Completed;
    }

    return UpdateResult::Updated;
}

IAction::UnitState ActionBuild::unitState() const
{
    Building::Ptr target = m_targetBuilding.lock();
    if (!target) {
        WARN << "target lost";
        return Idle;
    }

    if (target->data()->ID == Unit::Farm) {
        return Working;
    }

    return Proceeding;
}
