#include "ScenarioController.h"

#include <genie/script/ScnFile.h>

#include "mechanics/Unit.h"

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
        for (const genie::TriggerCondition &cond : trigger.conditions) {
            if (cond.type == genie::TriggerCondition::OwnObjects && cond.object >= 0) {

            }
        }
    }

    for (const Trigger &trigger : m_triggers) {
        DBG << trigger.data;
    }
}

void ScenarioController::onUnitCreated(Unit *unit)
{
    for (Trigger &trigger : m_triggers) {
        for (Condition &condition : trigger.conditions) {
            switch(condition.data.type) {
            case genie::TriggerCondition::OwnObjects:
                if (condition.checkUnitMatching(unit)) {
                    condition.amountRequired--;
                }
                continue;
            case genie::TriggerCondition::OwnFewerObjects:
                if (condition.checkUnitMatching(unit)) {
                    condition.amountRequired++;
                }
                break;
            default:
                continue;
            }
        }
    }
}

bool ScenarioController::Condition::checkUnitMatching(const Unit *unit) const
{
    if (!unit) {
        WARN << "null unit";
        return false;
    }

    if (data.sourcePlayer >= -1) {
        if (unit->playerId != data.sourcePlayer) {
            return false;
        }
    }

    if (data.objectType >= -1 && unit->data()->CombatLevel != data.objectType) {
        return false;
    }
    if (data.object >= -1 && unit->data()->ID != data.object) {
        return false;
    }

    return true;
}
