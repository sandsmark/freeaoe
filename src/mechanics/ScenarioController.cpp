#include "ScenarioController.h"

#include <genie/dat/Unit.h>
#include <genie/dat/ResourceUsage.h>
#include <genie/script/ScnFile.h>
#include <genie/script/scn/ScnPlayerData.h>
#include <genie/script/scn/Trigger.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "audio/AudioPlayer.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "mechanics/GameState.h"
#include "mechanics/UnitFactory.h"
#include "mechanics/Player.h"

#include "resource/LanguageManager.h"

#include "Engine.h"
#include "Entity.h"
#include "GameState.h"
#include "Player.h"
#include "Unit.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "core/ResourceMap.h"
#include "core/Types.h"
#include "global/EventManager.h"
#include "mechanics/Map.h"
#include "mechanics/ScenarioController.h"
#include "mechanics/UnitFactory.h"
#include "mechanics/UnitManager.h"

ScenarioController::ScenarioController(GameState *gameState) :
    m_gameState(gameState)
{
}

void ScenarioController::setScenario(const std::shared_ptr<genie::ScnFile> &scenario)
{
    m_triggers.clear();

    if (!scenario) {
        EventManager::deregisterListener(this);
        WARN << "set null scenario";
        return;
    }
    std::unordered_set<int32_t> missingConditionTypes;
    for (const genie::Trigger &trigger : scenario->triggers) {
        if (trigger.conditions.empty()) {
            m_triggers.emplace_back(trigger);
            continue;
        }

        bool isImplemented = false;
        for (const genie::TriggerCondition &cond : trigger.conditions) {
            switch(cond.type) { // Add here as they are implemented
            case genie::TriggerCondition::OwnObjects:
            case genie::TriggerCondition::OwnFewerObjects:
            case genie::TriggerCondition::ObjectSelected:
            case genie::TriggerCondition::ObjectsInArea:
            case genie::TriggerCondition::Timer:
            case genie::TriggerCondition::DestroyObject:
            case genie::TriggerCondition::AccumulateAttribute:
                isImplemented = true;
                break;
            default:
//                WARN << "Not implemented condition" << cond;
                missingConditionTypes.insert(cond.type);
                continue;
            }
        }

        if (isImplemented) {
            m_triggers.emplace_back(trigger);
        } else {
            DBG << trigger;
        }
    }

    for (const int32_t type : missingConditionTypes) {
        DBG << "Missing support for condition type" << genie::TriggerCondition::Type(type);
    }

    std::unordered_set<int32_t> missingEffectTypes;
    for (const Trigger &trigger : m_triggers) {
        for (const genie::TriggerEffect &effect : trigger.effects) {
            switch(effect.type) { // Add here as they are implemented
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

//    genie::Trigger mainVictoryTrigger;
//    DBG << "global victory type" << scenario->victoryType;
    const genie::ScnVictory &victoryConditions = scenario->playerData.victoryConditions;

    std::vector<genie::TriggerCondition> mainVictoryConditions;
    std::vector<genie::TriggerCondition> conquestConditions;
    if (victoryConditions.conquestRequired || victoryConditions.victoryMode == genie::ScnVictory::Conquest) {
        for (size_t playerId = 0; playerId < scenario->players.size(); playerId++) {
            if (!scenario->playerData.resourcesPlusPlayerInfo[playerId].enabled) {
                continue;
            }
            if (scenario->playerData.resourcesPlusPlayerInfo[playerId].isHuman) {
                continue;
            }
            genie::TriggerCondition condition;
            condition.type = genie::TriggerCondition::PlayerDefeated;
            condition.sourcePlayer = playerId;
            conquestConditions.push_back(std::move(condition));
        }
    }
    if (victoryConditions.conquestRequired) {
        DBG << "conquest required to win";
    }

    switch(victoryConditions.victoryMode) {
    case genie::ScnVictory::Standard:
        WARN << "TODO handle standard game";
        break;
    case genie::ScnVictory::Conquest:
        DBG << "conquest game (should be handled)";
        mainVictoryConditions = conquestConditions;
        break;
    case genie::ScnVictory::Score:
        WARN << "TODO handle score game";
        if (victoryConditions.scoreRequired > 0) {
            DBG << "requires" << victoryConditions.scoreRequired << "score to win";
            // TODO: create a condition for all score resourcetypes
        }
        break;
    case genie::ScnVictory::Timed:
        WARN << "TODO handle timed game";
        if (victoryConditions.timeForTimedGame > 0) {
            DBG << "requires" << victoryConditions.timeForTimedGame << "time to win";
            // TODO: create a timer condition
        }
        break;
    case genie::ScnVictory::Custom:
        WARN << "TODO: check if we handle custom game";
        break;
    default:
        WARN << "Invalid victory mode" << victoryConditions.victoryMode;
    }

    // I think relics and explored might be for custom games?
    if (victoryConditions.numRelicsRequired > 0) {
        DBG << "requires" << victoryConditions.numRelicsRequired << "relics to win";
        genie::TriggerCondition condition;
        condition.type = genie::TriggerCondition::AccumulateAttribute;
        condition.amount = victoryConditions.numRelicsRequired;
        condition.resource = int32_t(genie::ResourceType::RelicsCaptured);

        mainVictoryConditions.push_back(std::move(condition));
    }

    if (victoryConditions.exploredPerCentRequired > 0) {
        DBG << "requires" << victoryConditions.exploredPerCentRequired << "of map explored to win";
        genie::TriggerCondition condition;
        condition.type = genie::TriggerCondition::AccumulateAttribute;
        condition.amount = victoryConditions.exploredPerCentRequired;
        condition.resource = int32_t(genie::ResourceType::PercentMapExplored);
        mainVictoryConditions.push_back(std::move(condition));
    }


    genie::TriggerEffect humanWinsEffect;
    humanWinsEffect.type = genie::TriggerEffect::DeclareVictory;
    humanWinsEffect.sourcePlayer = m_gameState->humanPlayer()->playerId;
    if (scenario->playerData.victoryConditions.allConditionsRequired) {
        DBG << "all conditions required to win";
        genie::Trigger mainVictoryTrigger;
        mainVictoryTrigger.startingState = 1;
        mainVictoryTrigger.conditions = mainVictoryConditions;

        if (victoryConditions.conquestRequired && victoryConditions.victoryMode != genie::ScnVictory::Conquest) {
            for (const genie::TriggerCondition &conquestCondition : conquestConditions) {
                mainVictoryTrigger.conditions.push_back(conquestCondition);
            }
        }

        mainVictoryTrigger.effects = { humanWinsEffect };
        m_triggers.emplace_back(mainVictoryTrigger);
    } else {
        DBG << "any condition required to win";
        for (const genie::TriggerCondition &victoryCondition : mainVictoryConditions) {
            genie::Trigger mainVictoryTrigger;
            mainVictoryTrigger.startingState = 1;
            mainVictoryTrigger.conditions = { victoryCondition };

            if (victoryConditions.conquestRequired && victoryConditions.victoryMode != genie::ScnVictory::Conquest) {
                for (const genie::TriggerCondition &conquestCondition : conquestConditions) {
                    mainVictoryTrigger.conditions.push_back(conquestCondition);
                }
            }

            mainVictoryTrigger.effects = { humanWinsEffect };
            m_triggers.emplace_back(mainVictoryTrigger);
        }
        if (victoryConditions.conquestRequired || victoryConditions.victoryMode == genie::ScnVictory::Conquest) {
            genie::Trigger conquestTrigger;
            conquestTrigger.startingState = 1;
            conquestTrigger.conditions = conquestConditions;

            for (const genie::TriggerCondition &conquestCondition : conquestConditions) {
                conquestTrigger.conditions.push_back(conquestCondition);
            }

            conquestTrigger.effects = { humanWinsEffect };
            m_triggers.emplace_back(conquestTrigger);
        }
    }

    for (size_t playerId = 0; playerId < scenario->players.size(); playerId++) {
        const genie::ScnMorePlayerData &player  = scenario->players[playerId];
        genie::Trigger winTrigger;
        winTrigger.startingState = 1;
        winTrigger.name = player.playerName + " wins";

        for (const genie::ScnPlayerVictoryCondition &victoryCondition : player.victoryConditions) {
            switch(victoryCondition.type) {
            case genie::ScnPlayerVictoryCondition::Attribute: {
                DBG << "player" << player.playerName << "needs" << victoryCondition.count << "of" << genie::ResourceType(victoryCondition.number) << "to win";

                genie::TriggerCondition condition;
                condition.type = genie::TriggerCondition::AccumulateAttribute;
                condition.amount = victoryCondition.count;
                winTrigger.conditions = {condition};
                winTrigger.conditions.push_back(std::move(condition));

                break;
            }
            default:
                WARN << "unhandled victory condition type:" << victoryCondition.type;
                continue;
            }
        }
        if (winTrigger.conditions.empty()) {
            DBG << "no winning conditions for" << player.playerName;
            continue;
        }

        genie::TriggerEffect effect;
        effect.type = genie::TriggerEffect::DeclareVictory;
        if  (player.playerID >= 0) {
            effect.sourcePlayer = player.playerID;
        } else {
            effect.sourcePlayer = playerId;
        }

        winTrigger.effects = {effect};
        m_triggers.emplace_back(winTrigger);
    }

    EventManager::registerListener(this, EventManager::UnitCreated);
    EventManager::registerListener(this, EventManager::UnitMoved);
    EventManager::registerListener(this, EventManager::UnitSelected);
    EventManager::registerListener(this, EventManager::UnitDeselected);
    EventManager::registerListener(this, EventManager::UnitDestroyed);
    EventManager::registerListener(this, EventManager::PlayerDefeated);
    EventManager::registerListener(this, EventManager::AttributeChanged);
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

        if (!trigger.looping) {
            trigger.enabled = false;
        }

        for (const genie::TriggerEffect &effect : trigger.effects) {
            handleTriggerEffect(effect);
        }
    }

    return updated;
}

void ScenarioController::handleTriggerEffect(const genie::TriggerEffect &effect)
{
    switch(effect.type) {

         ////////////////////////
         // Trigger modifications
    case genie::TriggerEffect::ActivateTrigger:
        if (effect.trigger < 0 || effect.trigger >= m_triggers.size()) {
            DBG << "can't activate invalid trigger";
            return;
        }
        DBG << "enabling trigger" << m_triggers[effect.trigger].name;
        m_triggers[effect.trigger].enabled = true;
        break;
    case genie::TriggerEffect::DeactivateTrigger:
        if (effect.trigger < 0 || effect.trigger >= m_triggers.size()) {
            DBG << "can't deactivate invalid trigger";
            return;
        }
        DBG << "disabling trigger" << m_triggers[effect.trigger].name;
        m_triggers[effect.trigger].enabled = false;
        break;

        ///////////////
        // Chat stuff
    case genie::TriggerEffect::DisplayInstructions:
        AudioPlayer::instance().playStream("scenario/" + effect.soundFile + ".mp3");
        if (m_engine) {
            m_engine->addMessage(effect.message);
        } else {
            WARN << "missing engine" << effect.message << effect.soundFile;
        }
        break;

        ///////////////
        // Camera stuff
    case genie::TriggerEffect::ChangeView:
        DBG << "Moving camera" << effect;
        m_gameState->moveCameraTo(MapPos(effect.location.y * Constants::TILE_SIZE, effect.location.x * Constants::TILE_SIZE));
        break;

        /////////////
        // Tech stuff
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
        ///////////////
        // Object stuff
    case genie::TriggerEffect::CreateObject: {
        DBG << "Creating unit" << effect;
        Player::Ptr player = m_gameState->player(effect.sourcePlayer);
        if (!player) {
            WARN << "couldn't get player for effect";
            break;
        }
        MapPos location(effect.location.y * Constants::TILE_SIZE, effect.location.x * Constants::TILE_SIZE);
        Unit::Ptr unit = UnitFactory::Inst().createUnit(effect.object, player, *m_gameState->unitManager());
        if (!unit) {
            WARN << "Failed to create unit";
            return;
        }
        DBG << "Created" << unit->debugName;
        m_gameState->unitManager()->add(unit, location);
        break;
    }
    case genie::TriggerEffect::RemoveObject: {
        DBG << "Removing unit" << effect;
        forEachMatchingUnit(effect, [this](const Unit::Ptr &unit) {
            DBG << "Removing unit" << unit->debugName;
            m_gameState->unitManager()->remove(unit);
        });
        break;
    }
    case genie::TriggerEffect::TaskObject: {
        // again with the wtf swap of x and y
        // TODO, not sure if it is right to move to the middle of the tile, but whatevs
        MapPos targetPos(effect.location.y + 0.5, effect.location.x + 0.5);
        targetPos *= Constants::TILE_SIZE;

        forEachMatchingUnit(effect, [this, &targetPos](const Unit::Ptr &unit) {
            DBG << "Tasking object" << unit->debugName;
            m_gameState->unitManager()->moveUnitTo(unit, targetPos);
        });
        break;
    }
    case genie::TriggerEffect::DamageObject: {
        DBG << "Damaging object" << effect;
        forEachMatchingUnit(effect, [&](const Unit::Ptr &unit) {
            DBG << "Damaging unit" << unit->debugName << "for" << effect.amount;
            unit->takeDamage(effect.amount);
        });
        break;
    }
    case genie::TriggerEffect::ChangeObjectHP: {
        forEachMatchingUnit(effect, [&](const Unit::Ptr &unit) {
            const float deltaHP = effect.amount - unit->healthLeft();
            DBG << "Changing unit HP" << unit->debugName << "for" << effect.amount;
            unit->takeDamage(deltaHP);
        });
        break;
    }
    case genie::TriggerEffect::SetUnitStance: {
        Unit::Stance stance = Unit::Stance::Invalid;
        switch(effect.boundedValue) {
        case 1:
            stance = Unit::Stance::Aggressive;
            break;
        case 2:
            stance = Unit::Stance::Defensive;
            break;
        case 3:
            stance = Unit::Stance::StandGround;
            break;
        case 4:
            stance = Unit::Stance::NoAttack;
            break;
        default:
            WARN << "Invalid stance" << effect.boundedValue;
            break;
        }

        if (stance == Unit::Stance::Invalid) {
            break;
        }

        forEachMatchingUnit(effect, [&](const Unit::Ptr &unit) {
            unit->stance = stance;
        });
        break;
    }
    case genie::TriggerEffect::HD_HealObject: {
        forEachMatchingUnit(effect, [&](const Unit::Ptr &unit) {
            DBG << "Healing" << unit->debugName << "for" << effect.amount;
            unit->takeDamage(-effect.amount);
        });
        break;
    }
    case genie::TriggerEffect::ChangeObjectName:
        DBG << "TODO" << effect << "need to implement changeable display name";
        break;

        ////////////////////
        // Game ending stuff
    case genie::TriggerEffect::DeclareVictory: {
        if (m_engine) {
            m_engine->addMessage("");
            m_engine->addMessage("");
            m_engine->addMessage("           ----");
            m_engine->addMessage("u win prize congratilatons");
            m_engine->addMessage("sorry, victory is not implemented");
        }
        m_gameState->onPlayerWin(effect.sourcePlayer);
        break;
    }
    default:
        WARN << "not implemented trigger effect" << effect;
        break;
    }
}

void ScenarioController::forEachMatchingUnit(const genie::TriggerEffect &effect, const std::function<void (const Unit::Ptr &)> &action)
{
    std::vector<std::weak_ptr<Entity>> entities;
    entities = m_gameState->map()->entitiesBetween(effect.areaFrom.y,
                                                   effect.areaFrom.x,
                                                   effect.areaTo.y,
                                                   effect.areaTo.x);


    bool foundMatching = false;
    for (const std::weak_ptr<Entity> &entity : entities) {
        Unit::Ptr unit = Unit::fromEntity(entity);
        if (!unit) {
            WARN << "got invalid unit in area for effect";
            continue;
        }
        if (!checkUnitMatchingEffect(unit, effect)) {
            continue;
        }
        foundMatching = true;
        action(unit);
    }

    if (!foundMatching) {
        WARN << "Found no matching units for effect" << effect;
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
    (void)player;
    // TODO
}

void ScenarioController::onAttributeChanged(Player *player, int attributeId, float newValue)
{
    for (Trigger &trigger : m_triggers) {
        if (!trigger.enabled) {
            continue;
        }

        for (Condition &condition : trigger.conditions) {
            if (condition.data.type != genie::TriggerCondition::AccumulateAttribute) {
                continue;
            }
            if (condition.data.resource != attributeId) {
                continue;
            }
            if (condition.data.sourcePlayer != -1 && condition.data.sourcePlayer != player->playerId) {
                continue;
            }

            condition.amountRequired += newValue;
        }
    }
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
            case genie::TriggerCondition::OwnFewerObjects:
                if (condition.checkUnitMatching(unit)) {
                    condition.amountRequired--;
                    DBG << "fewer condition match" << unit->spawnId << unit->debugName << unit->id << condition.data << condition.amountRequired;
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
        if (unit->playerId() != data.sourcePlayer) {
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
        if (unit->playerId() != effect.sourcePlayer) {
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
