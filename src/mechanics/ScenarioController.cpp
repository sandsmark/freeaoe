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
        bool isImplemented = false;
        for (const genie::TriggerCondition &cond : trigger.conditions) {
            switch(cond.type) {
            case genie::TriggerCondition::OwnObjects:
            case genie::TriggerCondition::ObjectsInArea:
            case genie::TriggerCondition::ObjectSelected:
                isImplemented = true;
                break;
                break;
            case genie::TriggerCondition::Timer:
                isImplemented = true;
                if (trigger.startingState) {
                    DBG << "start state" << trigger.startingState;
                    DBG << "start time" << trigger.startingTime;
                    DBG << "condition time" << cond.timer << cond.amount;
                }
                continue;
            default:
                continue;
            }
        }

        if (isImplemented) {
            m_triggers.emplace_back(trigger);
        } else {
//            DBG << trigger;
        }
    }

//    for (const Trigger &trigger : m_triggers) {
//        DBG << trigger.data;
//    }
}

bool ScenarioController::update(Time time)
{
    bool updated = false;
    const Time elapsed = time - m_lastUpdateTime;
    m_lastUpdateTime = time;
    for (Trigger &trigger : m_triggers) {
        if (!trigger.enabled) {
            continue;
        }

        bool conditionsSatisfied = true;
        for (Condition &condition : trigger.conditions) {
            if (condition.data.type == genie::TriggerCondition::Timer) {
                condition.amountRequired -= elapsed;
            }

            if (condition.amountRequired > 0) {
                conditionsSatisfied = false;
            }
        }

        if (!conditionsSatisfied) {
            continue;
        }

        updated = true;

        if (!trigger.data.looping) {
            trigger.enabled = false;
        }

        for (const genie::TriggerEffect &effect : trigger.data.effects) {
            switch(effect.type) {
            case genie::TriggerEffect::ActivateTrigger:
                // TODO: display order or normal order?
                if (effect.trigger < 0 || effect.trigger >= m_triggers.size()) {
                    DBG << "can't activate invalid trigger";
                    continue;
                }
                DBG << "enabling trigger" << m_triggers[effect.trigger].data.name;
                m_triggers[effect.trigger].enabled = true;
                break;
            case genie::TriggerEffect::DisplayInstructions:
                WARN << "implement on screen message stuff";
                WARN << effect.message << effect.soundFile;
                break;
            default:
                DBG << "not implemented trigger effect" << effect;
                break;
            }
        }
    }

    return updated;
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
