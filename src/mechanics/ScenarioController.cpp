#include "ScenarioController.h"
#include "global/EventManager.h"

#include <genie/script/ScnFile.h>

#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "mechanics/GameState.h"
#include "mechanics/UnitFactory.h"

#include <set>

ScenarioController::ScenarioController()
{
    EventManager::registerListener(this, EventManager::UnitCreated);
    EventManager::registerListener(this, EventManager::UnitMoved);
    EventManager::registerListener(this, EventManager::UnitSelected);
    EventManager::registerListener(this, EventManager::UnitDeselected);
    EventManager::registerListener(this, EventManager::UnitDestroyed);
    EventManager::registerListener(this, EventManager::PlayerDefeated);
}

void ScenarioController::setScenario(const std::shared_ptr<genie::ScnFile> &scenario)
{
    m_triggers.clear();

    if (!scenario) {
        WARN << "set null scenario";
        return;
    }
    std::unordered_set<int32_t> missingConditionTypes;
    for (const genie::Trigger &trigger : scenario->triggers) {
        bool isImplemented = false;
        for (const genie::TriggerCondition &cond : trigger.conditions) {
            switch(cond.type) {
            case genie::TriggerCondition::OwnObjects:
            case genie::TriggerCondition::OwnFewerObjects:
            case genie::TriggerCondition::ObjectSelected:
            case genie::TriggerCondition::ObjectsInArea:
            case genie::TriggerCondition::Timer:
            case genie::TriggerCondition::DestroyObject:
                isImplemented = true;
                break;
            default:
                WARN << "Not implemented condition" << cond;
                continue;
            }
        }

        if (isImplemented) {
            m_triggers.emplace_back(trigger);
        } else {
//            DBG << trigger;
        }
    }

    std::unordered_set<int32_t> missingEffectTypes;
    for (const Trigger &trigger : m_triggers) {
        for (const genie::TriggerEffect &effect : trigger.data.effects) {
            switch(effect.type) {
            case genie::TriggerEffect::DeactivateTrigger:
            case genie::TriggerEffect::ActivateTrigger:
            case genie::TriggerEffect::DisplayInstructions:
            case genie::TriggerEffect::TaskObject:
            case genie::TriggerEffect::ChangeView:
            case genie::TriggerEffect::ResearchTechnology:
            case genie::TriggerEffect::CreateObject:
            case genie::TriggerEffect::RemoveObject:
            case genie::TriggerEffect::DeclareVictory:
                break;
            default:
                missingEffectTypes.insert(effect.type);
                break;
            }

        }
    }
    for (const int32_t type : missingEffectTypes) {
        WARN << "not implemented trigger effect" << genie::TriggerEffect::Type(type);
    }

    DBG << "global victory type" << scenario->victoryType;
    DBG << "main player victory type" << scenario->playerData.victoryConditions.victoryMode;
    DBG << "relics required:" << scenario->playerData.victoryConditions.numRelicsRequired;
    DBG << "conquest required:" << scenario->playerData.victoryConditions.conquestRequired;
    DBG << "explored percentage required:" << scenario->playerData.victoryConditions.exploredPerCentRequired;
    DBG << "all conditions required" << scenario->playerData.victoryConditions.allConditionsRequired;
    DBG << "score required" << scenario->playerData.victoryConditions.scoreRequired;
    DBG << "time required" << scenario->playerData.victoryConditions.timeForTimedGame;

//    for (const genie::ScnMorePlayerData &player : scenario->players) {
//        for (const genie::ScnPlayerVictoryCondition &victoryCondition : player.victoryConditions) {
//            switch(victoryCondition.type) {
//            case genie::ScnPlayerVictoryCondition::Attribute:
//                DBG << "player" << player.playerName << "needs" << victoryCondition.count << "of" << genie::ResourceType(victoryCondition.number) << "to win";
//                break;
//            default:
//                WARN << "unhandled victory condition type:" << victoryCondition.type;
//                break;
//            }
//        }
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
            handleTriggerEffect(effect);
        }
    }

    return updated;
}

void ScenarioController::handleTriggerEffect(const genie::TriggerEffect &effect)
{
    switch(effect.type) {
    case genie::TriggerEffect::ActivateTrigger:
        // TODO: display order or normal order?
        if (effect.trigger < 0 || effect.trigger >= m_triggers.size()) {
            DBG << "can't activate invalid trigger";
            return;
        }
        DBG << "enabling trigger" << m_triggers[effect.trigger].data.name;
        m_triggers[effect.trigger].enabled = true;
        break;
    case genie::TriggerEffect::DeactivateTrigger:
        // TODO: display order or normal order?
        if (effect.trigger < 0 || effect.trigger >= m_triggers.size()) {
            DBG << "can't deactivate invalid trigger";
            return;
        }
        DBG << "disabling trigger" << m_triggers[effect.trigger].data.name;
        m_triggers[effect.trigger].enabled = false;
        break;
    case genie::TriggerEffect::DisplayInstructions:
        DBG << "TODO: implement on screen message stuff and sound";
        WARN << effect.message << effect.soundFile;
        break;
    case genie::TriggerEffect::ChangeView:
        DBG << "Moving camera" << effect;
        m_gameState->moveCameraTo(MapPos(effect.location.y * Constants::TILE_SIZE, effect.location.x * Constants::TILE_SIZE));
        break;
    case genie::TriggerEffect::ResearchTechnology: {
        DBG << "Researching" << effect;
        Player::Ptr player = m_gameState->player(effect.sourcePlayer);
        if (!player) {
            WARN << "couldn't get player for effect";
            break;
        }
        player->applyResearch(effect.technology);
        break;
    }
    case genie::TriggerEffect::CreateObject: {
        DBG << "Creating unit" << effect;
        Player::Ptr player = m_gameState->player(effect.sourcePlayer);
        if (!player) {
            WARN << "couldn't get player for effect";
            break;
        }
        MapPos location(effect.location.y * Constants::TILE_SIZE, effect.location.x * Constants::TILE_SIZE);
        Unit::Ptr unit = UnitFactory::Inst().createUnit(effect.object, location, player, *m_gameState->unitManager());
        DBG << "Created" << unit->debugName;
        m_gameState->unitManager()->add(unit);
        break;
    }
    case genie::TriggerEffect::RemoveObject: {
        DBG << "Removing unit" << effect;
        std::vector<std::weak_ptr<Entity>> entities;
        entities = m_gameState->map()->entitiesBetween(effect.areaFrom.y,
                                                              effect.areaFrom.x,
                                                              effect.areaTo.y,
                                                              effect.areaTo.x);

        // TODO, not sure if it is right to move to the middle of the tile, but whatevs
        MapPos targetPos(effect.location.y + 0.5, effect.location.x + 0.5);
        targetPos *= Constants::TILE_SIZE;

        for (const std::weak_ptr<Entity> &entity : entities) {
            Unit::Ptr unit = Entity::asUnit(entity);
            if (!unit) {
                WARN << "got invalid unit in area for effect";
                continue;
            }
            if (!checkUnitMatchingEffect(unit, effect)) {
                continue;
            }

            DBG << "Removing unit" << unit->debugName;
            m_gameState->unitManager()->remove(unit);
        }
        break;
    }
    case genie::TriggerEffect::TaskObject: {
        // again with the wtf swap of x and y
        std::vector<std::weak_ptr<Entity>> entities;
        entities = m_gameState->map()->entitiesBetween(effect.areaFrom.y,
                                                              effect.areaFrom.x,
                                                              effect.areaTo.y,
                                                              effect.areaTo.x);

        // TODO, not sure if it is right to move to the middle of the tile, but whatevs
        MapPos targetPos(effect.location.y + 0.5, effect.location.x + 0.5);
        targetPos *= Constants::TILE_SIZE;

        for (const std::weak_ptr<Entity> &entity : entities) {
            Unit::Ptr unit = Entity::asUnit(entity);
            if (!unit) {
                WARN << "got invalid unit in area for effect";
                continue;
            }
            if (!checkUnitMatchingEffect(unit, effect)) {
                continue;
            }

            m_gameState->unitManager()->moveUnitTo(unit, targetPos);
        }
        break;
    }
    case genie::TriggerEffect::DeclareVictory: {
        m_gameState->onPlayerWin(effect.sourcePlayer);
        break;
    }
    default:
        WARN << "not implemented trigger effect" << effect;
        break;
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
            case genie::TriggerCondition::BringObjectToArea:
                WARN << "TODO: move objects to area" << condition.data;
                continue;
            case genie::TriggerCondition::ObjectsInArea:
                break;
            default:
                continue;
            }

            if (!condition.checkUnitMatching(unit)) {
                continue;
            }

            const MapRect conditionRect(MapPos(condition.data.areaFrom.y, condition.data.areaFrom.x),
                                        MapPos(condition.data.areaTo.y, condition.data.areaTo.x)
                );

            // Moved out of required area
            if (conditionRect.contains(oldTile) && !conditionRect.contains(newTile))  {
                DBG << unit->debugName << "moved to" << newTile << "out of" << conditionRect;
                condition.amountRequired++;
                continue;
            }

            // Moved into area
            if (!conditionRect.contains(oldTile) && conditionRect.contains(newTile))  {
                DBG << unit->debugName << "moved to" << newTile << "into" << conditionRect;
                condition.amountRequired--;
                continue;
            }
        }
    }

}

void ScenarioController::onUnitSelected(Unit *unit)
{
    // Don't check for trigger enabled here, the player might select before trigger is enabled
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
    // Don't check for trigger enabled here, the player might select before trigger is enabled
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

void ScenarioController::onPlayerDefeated(Player *player)
{
    // TODO
}

void ScenarioController::onUnitDying(Unit *unit)
{
    DBG << "unit died" << unit->debugName << unit->spawnId;
    for (Trigger &trigger : m_triggers) {
        if (!trigger.enabled) {
            continue;
        }

        for (Condition &condition : trigger.conditions) {
            switch(condition.data.type) {
            case genie::TriggerCondition::DestroyObject:
                if (condition.checkUnitMatching(unit)) {
                    condition.amountRequired--;
                    DBG << "destroy condition match" << unit->spawnId << unit->debugName << unit->id << condition.data << condition.amountRequired;
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

bool ScenarioController::checkUnitMatchingEffect(const std::shared_ptr<Unit> &unit, const genie::TriggerEffect &effect)
{
    if (!unit) {
        WARN << "null unit";
        return false;
    }

    if (effect.sourcePlayer > -1) {
        if (unit->playerId != effect.sourcePlayer) {
            return false;
        }
    }

    if (effect.objectType > -1 && unit->data()->CombatLevel != effect.objectType) {
        return false;
    }

    if (effect.object > -1 && unit->data()->ID != effect.object) {
        return false;
    }

    // could check area, but we already check it above, so meh


    return true;

}
