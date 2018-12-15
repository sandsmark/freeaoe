#include "Civilization.h"

#include "resource/DataManager.h"
#include "resource/LanguageManager.h"

#include <genie/dat/DatFile.h>
#include <genie/dat/Civ.h>
#include <genie/dat/Unit.h>
#include <genie/dat/DatFile.h>

const genie::Unit Civilization::nullUnit;

Civilization::Civilization(const int civId, const genie::DatFile &dataFile) :
    m_civId(civId),
    m_data(dataFile.Civs.at(civId))
{
    m_unitsData = m_data.Units;

    m_taskSwapUnits.resize(10);
    for (const genie::Unit &unit : m_unitsData) {
        if (!unit.Enabled) {
            continue;
        }
        if (unit.Creatable.TrainLocationID > 0) {
            m_creatableUnits[unit.Creatable.TrainLocationID].push_back(&unit);
        }

        const uint8_t swapGroup = unit.Action.TaskSwapGroup;
        if (swapGroup > 0) {
            if (swapGroup >= m_taskSwapUnits.size()) {
                m_taskSwapUnits.resize(swapGroup + 1);
            }

            m_taskSwapUnits[swapGroup].push_back(&unit);
        }
    }

    for (size_t i=0; i<dataFile.Techs.size(); i++) {
        const genie::Tech &research = dataFile.Techs.at(i);
        if (research.ResearchLocation <= 0) {
            continue;
        }
        if (research.Civ != m_civId) {
            continue;
        }

        m_techs[i] = research;
        m_researchAvailable[research.ResearchLocation].push_back(&m_techs.at(i));
    }

}

const std::vector<const genie::Unit *> Civilization::creatableUnits(int16_t creator) const
{
    if (creator != 118 && unit(creator).Action.TaskSwapGroup != 0) {
        creator = 118;
    }

    if (m_creatableUnits.find(creator) == m_creatableUnits.end()) {
        return std::vector<const genie::Unit*>();
    }

    return m_creatableUnits.at(creator);
}

const std::vector<const genie::Tech *> Civilization::researchAvailableAt(int16_t creator) const
{
    if (m_researchAvailable.find(creator) == m_researchAvailable.end()) {
        return std::vector<const genie::Tech*>();
    }

    return m_researchAvailable.at(creator);
}

const genie::Unit &Civilization::unit(const uint16_t id) const
{
    if (id >= m_unitsData.size()) {
        WARN << "Invalid unit id" << id;
        return nullUnit;
    }

    return m_unitsData.at(id);
}

const genie::Tech &Civilization::tech(const uint16_t id) const
{
    if (m_techs.find(id) == m_techs.end()) {
        return DataManager::nullTech;
    }

    return m_techs.at(id);
}

std::vector<const genie::Unit *> Civilization::swappableUnits(const uint16_t taskSwapGroup) const
{
    if (taskSwapGroup >= m_taskSwapUnits.size()) {
        return {};
    }

    return m_taskSwapUnits[taskSwapGroup];
}

const ResourceMap Civilization::startingResources() const
{
    ResourceMap ret;
    for (size_t i=0; i<m_data.Resources.size(); i++) {
        if (i >= int(genie::ResourceType::NumberOfTypes)) {
            WARN << "Too many resources" << i;
            break;
        }

        ret[genie::ResourceType(i)] = m_data.Resources[i];
    }

    return ret;
}

float Civilization::startingResource(const genie::ResourceType type) const
{
    return m_data.Resources[int(type)];
}

const genie::Unit &Civilization::unitData(unsigned id)
{
    if (id >= m_unitsData.size()) {
        WARN << "invalid unit id" << id;
        return DataManager::nullUnit;
    }

    return m_unitsData[id];
}

void Civilization::enableUnit(const uint16_t id)
{
    if (id >= m_unitsData.size()) {
        WARN << "invalid target unit" << id;
        return;
    }
    genie::Unit unit = m_unitsData[id];
    unit.Enabled = true;
    if (unit.Creatable.TrainLocationID > 0) {
        m_creatableUnits[unit.Creatable.TrainLocationID].push_back(&unit);
    }

    const uint8_t swapGroup = unit.Action.TaskSwapGroup;
    if (swapGroup > 0) {
        if (swapGroup >= m_taskSwapUnits.size()) {
            m_taskSwapUnits.resize(swapGroup + 1);
        }

        m_taskSwapUnits[swapGroup].push_back(&unit);
    }
}

template<typename T>
void modifyAttribute(T &value, const genie::EffectCommand &effect)
{
    switch (effect.Type) {
    case genie::EffectCommand::AttributeMultiplier:
        value *= effect.Amount;
        return;
    case genie::EffectCommand::RelativeAttributeModifier:
        value += effect.Amount;
        return;
    case genie::EffectCommand::AbsoluteAttributeModifier:
        value = effect.Amount;
        return;
    default:
        return;
    }
}

void Civilization::applyUnitAttributeModifier(const genie::EffectCommand &effect)
{
    if (effect.TargetUnit < 0 || effect.TargetUnit >= m_unitsData.size()) {
        WARN << "invalid target unit" << effect.TargetUnit;
        return;
    }
    genie::Unit &unitData = m_unitsData[effect.TargetUnit];

    using genie::EffectCommand;
    switch (effect.AttributeID) {
    case EffectCommand::HitPoints:
        modifyAttribute(unitData.HitPoints, effect);
        break;
    case EffectCommand::LineOfSight:
        modifyAttribute(unitData.LineOfSight, effect);
        break;
    case EffectCommand::GarrisonCapacity:
        modifyAttribute(unitData.GarrisonCapacity, effect);
        break;
    case EffectCommand::UnitSizeX:
        modifyAttribute(unitData.Size.x, effect);
        break;
    case EffectCommand::UnitSizeY:
        modifyAttribute(unitData.Size.y, effect);
        break;
    case EffectCommand::MovementSpeed:
        modifyAttribute(unitData.Speed, effect);
        break;
    case EffectCommand::RotationSpeed:
        modifyAttribute(unitData.Moving.RotationSpeed, effect);
        break;
    case EffectCommand::AttackReloadTime:
        modifyAttribute(unitData.Combat.ReloadTime, effect);
        break;
    case EffectCommand::AccuracyPercent:
        modifyAttribute(unitData.Combat.AccuracyPercent, effect);
        break;
    case EffectCommand::MaxRange:
        modifyAttribute(unitData.Combat.MaxRange, effect);
        break;
    case EffectCommand::WorkRate:
        modifyAttribute(unitData.Action.WorkRate, effect);
        break;
    case EffectCommand::CarryCapacity:
        modifyAttribute(unitData.ResourceCapacity, effect);
        break;
    case EffectCommand::BaseArmor:
        modifyAttribute(unitData.Combat.BaseArmor, effect);
        break;
    case EffectCommand::ProjectileUnit:
        WARN << "double check the target projectile unit we set here" << effect.Amount << effect.UnitClassID << effect.AttributeID;
        modifyAttribute(unitData.Combat.ProjectileUnitID, effect);
        break;
    case EffectCommand::IconGraphicsAngle:
        WARN << "double check the target icon id we set here" << effect.Amount << effect.UnitClassID << effect.AttributeID;
        modifyAttribute(unitData.IconID, effect);
        break;
    case EffectCommand::TerrainDefenseBonus:
        WARN << "double check terrain bonus we set here" << effect.Amount << effect.UnitClassID << effect.AttributeID;
        modifyAttribute(unitData.Combat.DefenseTerrainBonus, effect);
        break;
    case EffectCommand::EnableSmartProjectiles:
        modifyAttribute(unitData.Missile.SmartMode, effect);
        break;
    case EffectCommand::MinRange:
        modifyAttribute(unitData.Combat.MinRange, effect);
        break;
    case EffectCommand::MainResourceStorage:
        WARN << "Not sure what main resource is";
        modifyAttribute(unitData.ResourceCapacity, effect);
        break;
    case EffectCommand::BlastWidth:
        modifyAttribute(unitData.Combat.BlastWidth, effect);
        break;
    case EffectCommand::SearchRadius:
        modifyAttribute(unitData.Action.SearchRadius, effect);
        break;
    case EffectCommand::TrainTime:
        modifyAttribute(unitData.Creatable.TrainTime, effect);
        break;
    case EffectCommand::TotalMissiles:
        modifyAttribute(unitData.Creatable.TotalProjectiles, effect);
        break;
    case EffectCommand::MaxTotalMissiles:
        modifyAttribute(unitData.Creatable.MaxTotalProjectiles, effect);
        break;
    case EffectCommand::GarrisonHealRate:
        modifyAttribute(unitData.Building.GarrisonHealRate, effect);
        break;
    case EffectCommand::RegenerationRate:
        WARN << "Setting hero mode for regen rate, almost certainly wrong";
        modifyAttribute(unitData.Creatable.HeroMode, effect);
        break;

    // Specialized costs
    case EffectCommand::FoodCosts:
        for (genie::unit::Creatable::ResourceCost &cost : unitData.Creatable.ResourceCosts) {
            if (cost.Type != int(genie::ResourceType::FoodStorage)) {
                continue;
            }
            modifyAttribute(cost.Amount, effect);
        }
        break;
    case EffectCommand::WoodCosts:
        for (genie::unit::Creatable::ResourceCost &cost : unitData.Creatable.ResourceCosts) {
            if (cost.Type != int(genie::ResourceType::WoodStorage)) {
                continue;
            }
            modifyAttribute(cost.Amount, effect);
        }
        break;
    case EffectCommand::GoldCosts:
        for (genie::unit::Creatable::ResourceCost &cost : unitData.Creatable.ResourceCosts) {
            if (cost.Type != int(genie::ResourceType::GoldStorage)) {
                continue;
            }
            modifyAttribute(cost.Amount, effect);
        }
        break;
    case EffectCommand::StoneCosts:
        for (genie::unit::Creatable::ResourceCost &cost : unitData.Creatable.ResourceCosts) {
            if (cost.Type != int(genie::ResourceType::StoneStorage)) {
                continue;
            }
            modifyAttribute(cost.Amount, effect);
        }
        break;
    case EffectCommand::ResourceCosts:
        for (genie::unit::Creatable::ResourceCost &cost : unitData.Creatable.ResourceCosts) {
            modifyAttribute(cost.Amount, effect);
        }
        break;
    case EffectCommand::Armor:
        for (genie::unit::AttackOrArmor &armor : unitData.Combat.Armours) {
            if (armor.Class != effect.AttributeID) {
                continue;
            }
            modifyAttribute(armor.Amount, effect);
        }
        break;
    case EffectCommand::Attack:
        for (genie::unit::AttackOrArmor &attack : unitData.Combat.Attacks) {
            if (attack.Class != effect.AttributeID) {
                continue;
            }
            modifyAttribute(attack.Amount, effect);
        }
        break;

    default:
        WARN << "Unhandled attribute ID" << effect.AttributeID;
        return;
    }
}
