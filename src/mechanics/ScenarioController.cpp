#include "ScenarioController.h"
#include "global/EventManager.h"

#include <genie/script/ScnFile.h>

#include "mechanics/Unit.h"

#include <set>

ScenarioController::ScenarioController()
{
    EventManager::registerListener(this, EventManager::UnitCreated);
    EventManager::registerListener(this, EventManager::UnitMoved);
    EventManager::registerListener(this, EventManager::UnitSelected);
    EventManager::registerListener(this, EventManager::UnitDeselected);
}

void ScenarioController::setScenario(const std::shared_ptr<genie::ScnFile> &scenario)
{
    m_triggers.clear();

    if (!scenario) {
        WARN << "set null scenario";
        return;
    }
    for (const genie::Trigger &trigger : scenario->triggers) {
        bool isHandled = false;
        for (const genie::TriggerCondition &cond : trigger.conditions) {
            if (cond.type == genie::TriggerCondition::OwnObjects) {
                isHandled = true;
                continue;
            }
            if (cond.type == genie::TriggerCondition::OwnObjects) {
                isHandled = true;
                continue;
            }
            if (cond.type == genie::TriggerCondition::ObjectsInArea) {
                isHandled = true;
                continue;
            }
            if (cond.type == genie::TriggerCondition::ObjectSelected) {
                isHandled = true;
                continue;
            }
        }

        if (isHandled) {
            m_triggers.emplace_back(trigger);
        } else {
//            DBG << trigger;
        }
    }

    for (const Trigger &trigger : m_triggers) {
        DBG << trigger.data;
    }
}

void ScenarioController::onUnitCreated(Unit *unit)
{
    for (Trigger &trigger : m_triggers) {
        if (!trigger.enabled) {
            continue;
        }

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

void ScenarioController::onUnitMoved(Unit *unit, const MapPos &oldTile, const MapPos &newTile)
{
    for (Trigger &trigger : m_triggers) {
        if (!trigger.enabled) {
            continue;
        }

        for (Condition &condition : trigger.conditions) {
            switch(condition.data.type) {
            case genie::TriggerCondition::ObjectsInArea:
                break;
            default:
                continue;
            }
            if (!condition.checkUnitMatching(unit)) {
                continue;
            }

            const MapRect conditionRect(MapPos(condition.data.areaFrom.x, condition.data.areaFrom.y),
                                        MapPos(condition.data.areaTo.x, condition.data.areaTo.y)
                );

            // Moved out of required area
            if (conditionRect.contains(oldTile) && !conditionRect.contains(newTile))  {
                condition.amountRequired++;
                continue;
            }

            // Moved into area
            if (!conditionRect.contains(oldTile) && conditionRect.contains(newTile))  {
                condition.amountRequired--;
                continue;
            }
        }
    }

}

void ScenarioController::onUnitSelected(Unit *unit)
{
    for (Trigger &trigger : m_triggers) {
        for (Condition &condition : trigger.conditions) {
            switch(condition.data.type) {
            case genie::TriggerCondition::ObjectSelected:
                if (condition.checkUnitMatching(unit)) {
                    condition.amountRequired--;
                    DBG << "select condition match" << unit->spawnId << unit->debugName << unit->id << condition.data << condition.amountRequired;
                }
                break;
            default:
                continue;
            }
        }
    }
}

void ScenarioController::onUnitDeselected(const Unit *unit)
{
    for (Trigger &trigger : m_triggers) {
        for (Condition &condition : trigger.conditions) {
            switch(condition.data.type) {
            case genie::TriggerCondition::ObjectSelected:
                if (condition.checkUnitMatching(unit)) {
                    condition.amountRequired++;
                    DBG << "deselect condition match" << unit->spawnId << unit->debugName << unit->id << condition.data << condition.amountRequired;
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

    if (data.sourcePlayer > -1) {
        if (unit->playerId != data.sourcePlayer) {
            return false;
        }
    }

    if (data.objectType > -1 && unit->data()->CombatLevel != data.objectType) {
        return false;
    }

    if (data.object > -1 && unit->data()->ID != data.object) {
        return false;
    }

    if (data.setObject > -1 && unit->spawnId != data.setObject) {
        return false;
    }


    return true;
}
