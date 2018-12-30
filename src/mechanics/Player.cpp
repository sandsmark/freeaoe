#include "Player.h"
#include "mechanics/Civilization.h"
#include "mechanics/Unit.h"
#include "core/Logger.h"

#include <genie/dat/TechageEffect.h>
#include "resource/DataManager.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources) :
    playerId(id),
    civ(c),
    resourcesAvailable(civ->startingResources()),
    name("Player " + std::to_string(id))
{

    for (const std::pair<const genie::ResourceType, float> &r : startingResources) {
        resourcesAvailable[r.first] = r.second;
    }

}
void Player::applyTech(const int effectId)
{
    const genie::Effect &effect = DataManager::Inst().getEffect(effectId);
    DBG << "Applying" << effect.Name;

    for (const genie::EffectCommand &command : effect.EffectCommands) {
        applyTechEffect(command);
    }
}

void Player::applyTechEffect(const genie::EffectCommand &effect)
{
    switch(effect.Type) {
    case genie::EffectCommand::ResourceModifier:
        if (effect.UnitClassID) {
            resourcesAvailable[genie::ResourceType(effect.TargetUnit)] += effect.Amount;
        } else {
            resourcesAvailable[genie::ResourceType(effect.TargetUnit)] = effect.Amount;
        }
        break;
    case genie::EffectCommand::EnableUnit:
        civ->enableUnit(effect.TargetUnit);
        break;
    case genie::EffectCommand::UpgradeUnit: {
        uint16_t fromUnitID = effect.TargetUnit;
        const genie::Unit &toUnitData = civ->unitData(effect.UnitClassID);
        if (toUnitData.Class == genie::Unit::InvalidClass) {
            return;
        }

        for (Unit *unit : m_units) {
            if (unit->data()->ID != fromUnitID) {
                continue;
            }
            unit->setUnitData(toUnitData);
        }
        break;
    }

    case genie::EffectCommand::AttributeMultiplier:
    case genie::EffectCommand::AbsoluteAttributeModifier:
    case genie::EffectCommand::RelativeAttributeModifier:
        civ->applyUnitAttributeModifier(effect);
        break;
    case genie::EffectCommand::ResourceMultiplier:
        resourcesAvailable[genie::ResourceType(effect.TargetUnit)] *= effect.Amount;
        break;
    case genie::EffectCommand::TechCostModifier:
        WARN << "Disable tech cost modifier not implemented";
        break;
    case genie::EffectCommand::DisableTech:
        WARN << "Disable tech effect not implemented";
        return;
    case genie::EffectCommand::TechTimeModifier:
        WARN << "Disable tech time modifier not implemented";
        break;
    default:
        WARN << "Unhandled tech effect type" << effect.Type;
        return;
    }

}

void Player::addUnit(Unit *unit)
{
    for (const genie::Unit::ResourceStorage &res : unit->data()->ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }
        switch (res.Type) {
        case genie::ResourceStoreMode::GiveResourceType:
        case genie::ResourceStoreMode::GiveAndTakeResourceType:
        case genie::ResourceStoreMode::BuildingResourceType:
            if (res.Amount < 0) {
                resourcesUsed[genie::ResourceType(res.Type)] -= res.Amount;
            } else {
                resourcesAvailable[genie::ResourceType(res.Type)] += res.Amount;
            }
            break;
        default:
            break;
        }
    }
    m_units.insert(unit);
}

void Player::removeUnit(Unit *unit)
{
    for (const genie::Unit::ResourceStorage &res : unit->data()->ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }
        switch (res.Type) {
        case genie::ResourceStoreMode::GiveAndTakeResourceType:
        case genie::ResourceStoreMode::BuildingResourceType:
            if (res.Amount < 0) {
                resourcesUsed[genie::ResourceType(res.Type)] += res.Amount;
            } else {
                resourcesAvailable[genie::ResourceType(res.Type)] -= res.Amount;
            }
            break;
        default:
            break;
        }
    }
    m_units.insert(unit);
    m_units.erase(unit);
}
