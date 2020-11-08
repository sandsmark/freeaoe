#pragma once

#include "global/EventListener.h"
#include "core/Logger.h"
#include "core/Types.h"

#include <genie/script/scn/Trigger.h>

#include <functional>

class GameState;
class Engine;
struct Unit;

namespace genie {
class ScnFile;
}

class ScenarioController : public EventListener
{
    struct Condition {
        /// For boolean triggers just 0 or 1
        /// For timers, milliseconds elapsed
        float amountRequired = 0;

        Condition(const genie::TriggerCondition &d) : data(d) {
            if (d.type == genie::TriggerCondition::Timer) {
                amountRequired = 1000 * data.timer; // it is in milliseconds
            } else if (data.amount > 0) {
                amountRequired = data.amount;
            } else {
                amountRequired = 1;
            }
        }
        const genie::TriggerCondition data;

        bool checkUnitMatching(const Unit *unit) const;
    };

    struct Trigger {
        bool enabled = false;

        Trigger (const genie::Trigger &d) :
            effects(d.effects),
            looping(d.looping),
            name(d.name)
        {
            if (d.startingState) {
                enabled = true;
            }

            for (const genie::TriggerCondition &cond : d.conditions) {
                conditions.emplace_back(cond);
            }
        }

        bool isSatisfied() const {
            if (!enabled) {
                return false;
            }
            for (const Condition &condition : conditions) {
                if (condition.amountRequired > 0) {
                    return false;
                }
            }

            return true;
        }

        std::vector<Condition> conditions;
        const std::vector<genie::TriggerEffect> effects;


        const bool looping = false;
        const std::string name;
    };

public:
    ScenarioController(GameState *gameState);

    void setScenario(const std::shared_ptr<genie::ScnFile> &scenario);
    bool update(Time time);

    // a bit ugly violation of blah blah composition, but w/e
    void setEngine(Engine *engine) { m_engine = engine; }

private:
    bool checkUnitMatchingEffect(const std::shared_ptr<Unit> &unit, const genie::TriggerEffect &effect);

    void onUnitDying(Unit *unit) override;
    void onUnitCreated(Unit *unit) override;
    void onUnitMoved(Unit *unit, const MapPos &oldTile, const MapPos &newTile) override;
    void onUnitSelected(Unit *unit) override;
    void onUnitDeselected(const Unit *unit) override;
    void onPlayerDefeated(Player *player) override;
    void onAttributeChanged(Player *player, int attributeId, float newValue) override;

    void handleTriggerEffect(const genie::TriggerEffect &effect);
    void forEachMatchingUnit(const genie::TriggerEffect &effect, const std::function<void(const std::shared_ptr<Unit> &)> &action);

    // Todo: put these in an std::array based on type, so we don't have to loop over all
    std::vector<Trigger> m_triggers;
    Time m_lastUpdateTime = 0;

    GameState *m_gameState = nullptr; // ugly raw pointer, but owned by gamestate, so sue me
    Engine *m_engine = nullptr; // samesies
//    Time m_nextTimerTriggerTarget = -1;

};

// Just debug print support beneath this, don't bother reading on (and it should be moved into a separate header)

inline void printGenieTriggerConditionType(LogPrinter &os, const genie::TriggerCondition::Type &type)
{
    // Generated with VIM™:
    //      :%s- \+\(.*\),.*-case genie::TriggerCondition::\1: os << "\1"; break;-
    switch(type) {
    case genie::TriggerCondition::None: os << "None"; break;
    case genie::TriggerCondition::BringObjectToArea: os << "BringObjectToArea"; break;
    case genie::TriggerCondition::BringObjectToObject: os << "BringObjectToObject"; break;
    case genie::TriggerCondition::OwnObjects: os << "OwnObjects"; break;
    case genie::TriggerCondition::OwnFewerObjects: os << "OwnFewerObjects"; break;
    case genie::TriggerCondition::ObjectsInArea: os << "ObjectsInArea"; break;
    case genie::TriggerCondition::DestroyObject: os << "DestroyObject"; break;
    case genie::TriggerCondition::CaptureObject: os << "CaptureObject"; break;
    case genie::TriggerCondition::AccumulateAttribute: os << "AccumulateAttribute"; break;
    case genie::TriggerCondition::ResearchTehcnology: os << "ResearchTehcnology"; break;
    case genie::TriggerCondition::Timer: os << "Timer"; break;
    case genie::TriggerCondition::ObjectSelected: os << "ObjectSelected"; break;
    case genie::TriggerCondition::AISignal: os << "AISignal"; break;
    case genie::TriggerCondition::PlayerDefeated: os << "PlayerDefeated"; break;
    case genie::TriggerCondition::ObjectHasTarget: os << "ObjectHasTarget"; break;
    case genie::TriggerCondition::ObjectVisible: os << "ObjectVisible"; break;
    case genie::TriggerCondition::ObjectNotVisible: os << "ObjectNotVisible"; break;
    case genie::TriggerCondition::ResearchingTechnology: os << "ResearchingTechnology"; break;
    case genie::TriggerCondition::UnitsGarrisoned: os << "UnitsGarrisoned"; break;
    case genie::TriggerCondition::DifficultyLevel: os << "DifficultyLevel"; break;
    case genie::TriggerCondition::HD_Chance: os << "HD_Chance = SWGB_OwnFewerFoundations"; break;
    case genie::TriggerCondition::SWGB_SelectedObjectsInArea: os << "SWGB_SelectedObjectsInArea"; break;
    case genie::TriggerCondition::SWGB_PoweredObjectsInArea: os << "SWGB_PoweredObjectsInArea"; break;
    case genie::TriggerCondition::SWGB_UnitsQueuedPastPopCap: os << "SWGB_UnitsQueuedPastPopCap"; break;
    default: os << "Invalid"; break;
    }
    os << " (" << int32_t(type) << ")";
}

inline LogPrinter operator <<(LogPrinter os, const genie::TriggerCondition::ObjectType type) {
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::TriggerCondition::ObjectType::";

    // same as genie::Unit
    switch(type) {
    case genie::TriggerCondition::Undefined: os << "Undefined"; break;
    case genie::TriggerCondition::Other: os << "Other"; break;
    case genie::TriggerCondition::Base: os << "Base"; break;
    case genie::TriggerCondition::Building: os << "Building"; break;
    case genie::TriggerCondition::Civilian: os << "Civilian"; break;
    case genie::TriggerCondition::Military: os << "Military"; break;
    default: os << "Invalid"; break;
    }

    os << " (" << int32_t(type) << ")";

    os << separator;
    os.separator = separator;

    return os;
}


inline LogPrinter operator <<(LogPrinter os, const genie::TriggerCondition::Type &type) {
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::TriggerCondition::Type::";

    printGenieTriggerConditionType(os, type);

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const genie::TriggerCondition &condition)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::TriggerCondition(";

    printGenieTriggerConditionType(os, genie::TriggerCondition::Type(condition.type));
    if (condition.type == genie::TriggerCondition::None) {
        os << ")" << separator;
        os.separator = separator;
        return os;
    }

    // Generated with VIM™:
    //      :%s-.* \(.*\) =.*-if (condition.\1 >= 0) os << ", \1 = " << condition.\1;-

    if (condition.usedVariables != 0x10) os << ", usedVariables = " << condition.usedVariables;
    if (condition.amount >= 0) os << ", amount = " << condition.amount;
    if (condition.resource >= 0) os << ", resource = " << condition.resource;
    if (condition.setObject >= 0) os << ", setObject = " << condition.setObject;
    if (condition.nextObject >= 0) os << ", nextObject = " << condition.nextObject;
    if (condition.object >= 0) os << ", object = " << condition.object;
    if (condition.sourcePlayer >= 0) os << ", sourcePlayer = " << condition.sourcePlayer;
    if (condition.technology >= 0) os << ", technology = " << condition.technology;
    if (condition.timer >= 0) os << ", timer = " << condition.timer;
    if (condition.trigger >= 0) os << ", trigger = " << condition.trigger;
    if (condition.objectGroup >= 0) os << ", objectGroup = " << condition.objectGroup;
    if (condition.objectType >= 0) os << ", objectType = " << genie::TriggerCondition::ObjectType(condition.objectType);
    if (condition.aiSignal >= 0) os << ", aiSignal = " << condition.aiSignal;

    if (condition.areaFrom.x != -1 || condition.areaFrom.y != -1) os << ", areaFrom = " << condition.areaFrom.x << "," << condition.areaFrom.y;
    if (condition.areaTo.x != -1 || condition.areaTo.y != -1) os << ", areaTo = " << condition.areaTo.x << "," << condition.areaTo.y;

    os << ")" << separator;
    os.separator = separator;

    return os;
}

inline void printGenieTriggerEffectType(LogPrinter &os, const genie::TriggerEffect::Type &type)
{

    // Generated with VIM™:
    //      :%s- \+\(.*\),.*-case genie::TriggerEffect::\1: os << "\1"; break;-
    // And some manual fixup because of the duplicates between HD/userpatch/SWGB
    // TODO (but not very important); check gameversion and fix automatically
    switch(type) {
    case genie::TriggerEffect::None: os << "None"; break;
    case genie::TriggerEffect::ChangeDiplomacy: os << "ChangeDiplomacy"; break;
    case genie::TriggerEffect::ResearchTechnology: os << "ResearchTechnology"; break;
    case genie::TriggerEffect::SendChat: os << "SendChat"; break;
    case genie::TriggerEffect::Sound: os << "Sound"; break;
    case genie::TriggerEffect::SendTribute: os << "SendTribute"; break;
    case genie::TriggerEffect::UnlockGate: os << "UnlockGate"; break;
    case genie::TriggerEffect::LockGate: os << "LockGate"; break;
    case genie::TriggerEffect::ActivateTrigger: os << "ActivateTrigger"; break;
    case genie::TriggerEffect::DeactivateTrigger: os << "DeactivateTrigger"; break;
    case genie::TriggerEffect::AIScriptGoal: os << "AIScriptGoal"; break;
    case genie::TriggerEffect::CreateObject: os << "CreateObject"; break;
    case genie::TriggerEffect::TaskObject: os << "TaskObject"; break;
    case genie::TriggerEffect::DeclareVictory: os << "DeclareVictory"; break;
    case genie::TriggerEffect::KillObject: os << "KillObject"; break;
    case genie::TriggerEffect::RemoveObject: os << "RemoveObject"; break;
    case genie::TriggerEffect::ChangeView: os << "ChangeView"; break;
    case genie::TriggerEffect::Unload: os << "Unload"; break;
    case genie::TriggerEffect::ChangeOwnership: os << "ChangeOwnership"; break;
    case genie::TriggerEffect::Patrol: os << "Patrol"; break;
    case genie::TriggerEffect::DisplayInstructions: os << "DisplayInstructions"; break;
    case genie::TriggerEffect::ClearInstructions: os << "ClearInstructions"; break;
    case genie::TriggerEffect::SetUnitStance: os << "SetUnitStance"; break;
    case genie::TriggerEffect::UseAdvancedButtons: os << "UseAdvancedButtons"; break;
    case genie::TriggerEffect::DamageObject: os << "DamageObject"; break;
    case genie::TriggerEffect::PlaceFoundation: os << "PlaceFoundation"; break;
    case genie::TriggerEffect::ChangeObjectName: os << "ChangeObjectName"; break;
    case genie::TriggerEffect::ChangeObjectHP: os << "ChangeObjectHP"; break;
    case genie::TriggerEffect::ChangeObjectAttack: os << "ChangeObjectAttack"; break;
    case genie::TriggerEffect::StopUnit: os << "StopUnit"; break;
    case genie::TriggerEffect::HD_AttackMove: os << "HD_AttackMove = SWGB_SnapView = UserPatch_ChangeSpeed"; break;
    case genie::TriggerEffect::HD_ChangeArmor: os << "HD_ChangeArmor = SWGB_DisableAdvancedButtons = UserPatch_ChangeRange"; break;
    case genie::TriggerEffect::HD_ChangeRange: os << "HD_ChangeRange = SWGB_EnableTech = UserPatch_ChangeMeleArmor"; break;
    case genie::TriggerEffect::HD_ChangeSpeed: os << "HD_ChangeSpeed = genie::TriggerEffect::SWGB_DisableTech = UserPatch_ChangePiercingArmor"; break;
    case genie::TriggerEffect::HD_HealObject: os << "HD_HealObject = SWGB_EnableUnit"; break;
    case genie::TriggerEffect::HD_TeleportObject: os << "HD_TeleportObject = SWGB_DisableUnit"; break;
    case genie::TriggerEffect::HD_ChangeUnitStance: os << "HD_ChangeUnitStance = SWGB_FlashUnit"; break;
    case genie::TriggerEffect::SWGBCC_InputOff: os << "SWGBCC_InputOff"; break;
    case genie::TriggerEffect::SWGBCC_InputOn: os << "SWGBCC_InputOn"; break;
    default: os << "Invalid";break;// (" << int32_t(type) << ")"; break;
    }
    os << " (" << int32_t(type) << ")";

}

inline LogPrinter operator <<(LogPrinter os, const genie::TriggerEffect::Type &type)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::TriggerEffect::Type::";
    printGenieTriggerEffectType(os, type);

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const genie::MapPoint &pos)
{
    const char *separator = os.separator;
    os.separator = "";
    os << "genie::MapPoint(x: " << pos.x << ", y: " << pos.y << ")" << separator;
    os.separator = separator;
    return os;
}

inline LogPrinter operator <<(LogPrinter os, const genie::TriggerEffect &effect)
{
    const char *separator = os.separator;
    os.separator = "";

    // Generated with VIM™:
    //      :%s-.* \(.*\) =.*-if (effect.\1 >= 0) os << ", \1 = " << effect.\1;-

    os << "genie::TriggerEffect(";
    printGenieTriggerEffectType(os, genie::TriggerEffect::Type(effect.type));// genie::TriggerEffect::Type(effect.type);
    if (effect.type == genie::TriggerEffect::None) {
        os << ")" << separator;
        os.separator = separator;
        return os;
    }

    if (effect.usedVariables != 23) os << ", usedVariables = " << effect.usedVariables;
    if (effect.aiGoal >= 0) os << ", aiGoal = " << effect.aiGoal;
    if (effect.amount >= 0) os << ", amount = " << effect.amount;
    if (effect.resource >= 0) os << ", resource = " << effect.resource;
    if (effect.diplomacy >= 0) os << ", diplomacy = " << effect.diplomacy;
    if (effect.setObjects >= 0) os << ", setObjects = " << effect.setObjects;
    if (effect.nextObject >= 0) os << ", nextObject = " << effect.nextObject;
    if (effect.object >= 0) os << ", object = " << effect.object;
    if (effect.sourcePlayer >= 0) os << ", sourcePlayer = " << effect.sourcePlayer;
    if (effect.targetPlayer >= 0) os << ", targetPlayer = " << effect.targetPlayer;
    if (effect.technology >= 0) os << ", technology = " << effect.technology;
    if (effect.stringTableID >= 0) os << ", stringTableID = " << effect.stringTableID;
    if (effect.soundResourceID >= 0) os << ", soundResourceID = " << effect.soundResourceID;
    if (effect.timer >= 0) os << ", timer = " << effect.timer;
    if (effect.trigger >= 0) os << ", trigger = " << effect.trigger;
    if (effect.objectGroup >= 0) os << ", objectGroup = " << effect.objectGroup;
    if (effect.objectType >= 0) os << ", objectType = " << effect.objectType;

    if (effect.location.x != -1 || effect.location.y != -1) os << ", location = " << effect.location.x << "," <<  effect.location.y;
    if (effect.areaFrom.x != -1 || effect.areaFrom.y != -1) os << ", areaFrom = " << effect.areaFrom.x << "," <<  effect.areaFrom.y;
    if (effect.areaTo.x != -1 || effect.areaTo.y != -1) os << ", areaTo = " << effect.areaTo.x << "," <<  effect.areaTo.y;

    if (effect.objectGroup >= 0) os << ", objectGroup = " << effect.objectGroup;
    if (effect.objectType >= 0) os << ", objectType = " << effect.objectType;
    if (effect.boundedValue >= 0) os << ", boundedValue = " << effect.boundedValue;

    if (!effect.message.empty()) os << ", message = " << effect.message;
    if (!effect.soundFile.empty()) os << ", soundFile = " << effect.soundFile;

    if (!effect.selectedUnits.empty()) {
        os << ", selectedUnits=[";
        for (const int32_t unit : effect.selectedUnits) {
            os << ", " << unit;
        }
    }

    os << ")" << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const genie::Trigger &trigger)
{
    const char *separator = os.separator;
    os.separator = "";

    // Generated with VIM™:
    //      :%s-.* \(.*\) =.*-if (effect.\1 >= 0) os << ", \1 = " << effect.\1;-

    os << "genie::Trigger(";
    os << "startingState = ";
    if (trigger.startingState == 1) {
        os << "enabled";
    } else if (trigger.startingState == 0) {
        os << "disabled";
    } else {
        os << trigger.startingState;
    }

    if (trigger.looping >= 0) os << ", looping = " << bool(trigger.looping);
    if (trigger.stringTableID >= 0) os << ", stringTableID = " << trigger.stringTableID;
    if (trigger.isObjective >= 0) os << ", isObjective = " << bool(trigger.isObjective);
    if (trigger.descriptionOrder >= 0) os << ", descriptionOrder = " << trigger.descriptionOrder;
    if (trigger.startingTime >= 0) os << ", startingTime = " << trigger.startingTime;

    if (!trigger.description.empty()) os << ", description = " << trigger.description;
    if (!trigger.name.empty()) os << ", name = " << trigger.name;

    if (!trigger.conditions.empty()) {
        os << ",\n\tconditions = {";

        for (size_t i = 0; i<trigger.conditions.size(); i++) {
            os << "\n\t\t" << trigger.conditionDisplayOrder[i] << ": " << trigger.conditions[i];
        }
        os << "\n\t}";
    }

    if (!trigger.effects.empty()) {
        os << ",\n\teffects = {";

        for (size_t i = 0; i<trigger.effects.size(); i++) {
            os << "\n\t\t" << trigger.effectDisplayOrder[i] << ": " << trigger.effects[i];
        }
        os << "\n\t}";
    }

//    if (!trigger.effectDisplayOrder.empty()) os << ", effectDisplayOrder = " << trigger.effectDisplayOrder;
//    if (!trigger.conditionDisplayOrder.empty()) os << ", conditionDisplayOrder = " << trigger.conditionDisplayOrder;

    os << ")" << separator;
    if (!trigger.effects.empty() || !trigger.conditions.empty()) {
        os << "\n";
    }

    os.separator = separator;

    return os;
}

