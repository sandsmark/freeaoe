#include "ScenarioController.h"

#include <genie/script/ScnFile.h>

#include <set>

ScenarioController::ScenarioController()
{

}

void ScenarioController::setScenario(const std::shared_ptr<genie::ScnFile> &scenario)
{
    m_triggers.clear();

    if (!scenario) {
        WARN << "set null scenario";
        return;
    }
    for (const genie::Trigger &trigger : scenario->triggers) {
        m_triggers.emplace_back(trigger);
    }

    for (const Trigger &trigger : m_triggers) {
        DBG << trigger.data;
    }
}

void ScenarioController::onUnitCreated(Unit *unit)
{
    (void)unit;
}
