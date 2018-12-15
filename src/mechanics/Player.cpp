#include "Player.h"
#include "mechanics/Civilization.h"
#include "mechanics/Unit.h"
#include "core/Logger.h"

#include <genie/dat/TechageEffect.h>
#include "resource/DataManager.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources) :
    playerId(id),
    civ(c),
    resources(civ->startingResources()),
    name("Player " + std::to_string(id))
{

    for (const std::pair<const genie::ResourceType, float> &r : startingResources) {
        resources[r.first] = r.second;
    }

}

void Player::applyTechEffect(const genie::EffectCommand &effect)
{
    switch(effect.Type) {
    case genie::EffectCommand::ResourceModifier:
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
        resources[genie::ResourceType(effect.TargetUnit)] *= effect.Amount;
        break;
    case genie::EffectCommand::TechCostModifier:
        break;
    case genie::EffectCommand::DisableTech:
        WARN << "Disable tech effect not implemented";
        return;
    case genie::EffectCommand::TechTimeModifier:
        break;
    default:
        WARN << "Unhandled tech effect type" << effect.Type;
        return;
    }

}

void Player::addUnit(Unit *unit)
{
    m_units.insert(unit);
}

void Player::removeUnit(Unit *unit)
{
    m_units.erase(unit);
}
