#include "ActionBuild.h"

#include <genie/dat/Unit.h>

namespace act {

ActionBuild::ActionBuild(Unit::Ptr builder, Unit::Ptr building) : IAction(Type::Build),
    m_unit(builder),
    m_targetBuilding(building),
    m_prevTime(0)
{
    building->constructors++;
}

ActionBuild::~ActionBuild()
{
    Unit::Ptr building = m_targetBuilding.lock();

    if (building) {
        building->constructors--;
    }
}

bool ActionBuild::update(Time time)
{
    if (!m_prevTime) {
        m_prevTime = time;
        return false;
    }

    Unit::Ptr building = m_targetBuilding.lock();

    if (building->creationProgress() >= 1.) {
        return true;
    }
    float progress = 3. / (building->constructors + 2.);
    progress *= (time - m_prevTime) * 0.0015;
    m_prevTime = time;

    building->increaseCreationProgress(progress);

    if (building->creationProgress() >= 1.) {
        return true;
    }
    return false;
}

}//namespace act
