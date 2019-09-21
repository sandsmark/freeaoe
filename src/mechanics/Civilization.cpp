#include "Civilization.h"

#include "resource/DataManager.h"
#include "resource/LanguageManager.h"

#include <genie/dat/DatFile.h>
#include <genie/dat/Civ.h>
#include <genie/dat/Unit.h>
#include <genie/dat/DatFile.h>

const genie::Unit Civilization::nullUnit;

Civilization::Civilization(const int civId) :
    m_civId(civId),
    m_data(DataManager::Inst().civilization(civId))
{
    applyData(m_data);
}

const std::vector<const genie::Unit *> &Civilization::creatableUnits(int16_t creator) const
{
    if (creator != 118 && unit(creator).Action.TaskSwapGroup != 0) {
        creator = 118;
    }

    if (m_creatableUnits.find(creator) == m_creatableUnits.end()) {
        static const std::vector<const genie::Unit*> nullVector;
        return nullVector;
    }

    return m_creatableUnits.at(creator);
}

const std::vector<const genie::Tech *> &Civilization::researchAvailableAt(int16_t creator) const
{
    if (m_researchAvailable.find(creator) == m_researchAvailable.end()) {
        static const std::vector<const genie::Tech*> nullVector;
        return nullVector;
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
        WARN << "invalid tech" << id;
        static const genie::Tech nullTech;
        return nullTech;
    }

    return m_techs.at(id);
}

const std::vector<const genie::Unit *> &Civilization::swappableUnits(const uint16_t taskSwapGroup) const
{
    if (taskSwapGroup >= m_taskSwapUnits.size()) {
        static const std::vector<const genie::Unit*> nullVector;
        return nullVector;
    }

    return m_taskSwapUnits[taskSwapGroup];
}

float Civilization::startingResource(const genie::ResourceType type) const
{
    return m_data.Resources[int(type)];
}

const genie::Unit &Civilization::unitData(unsigned id) const
{
    if (id >= m_unitsData.size()) {
        WARN << "invalid unit id" << id;
        static const genie::Unit nullUnit;
        return nullUnit;
    }

    return m_unitsData[id];
}

void Civilization::enableUnit(const uint16_t id)
{
    if (id >= m_unitsData.size()) {
        WARN << "invalid target unit" << id;
        return;
    }
    genie::Unit &unit = m_unitsData[id];
    unit.Enabled = true;
    if (unit.Creatable.TrainLocationID > 0) {
        m_creatableUnits[unit.Creatable.TrainLocationID].push_back(&unit);
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
    DBG << "Applying" << genie::EffectCommand::Attributes(effect.AttributeID);
    if (effect.TargetUnit >= 0) {
        applyUnitAttributeModifier(effect, effect.TargetUnit);
    } else if (effect.UnitClassID >= 0) {
        for (const genie::Unit &unitData : m_unitsData) {
            if (unitData.Class != effect.UnitClassID) {
                continue;
            }
            applyUnitAttributeModifier(effect, unitData.ID);
        }
    } else {
        WARN << "Can't apply effect with neither unit id or class id";
    }
}

void Civilization::setGaiaOverrideCiv(const int civId)
{
    applyData(DataManager::Inst().civilization(civId));
}

void Civilization::applyData(const genie::Civ &data)
{
    DBG << "Applying for civ";

    if (data.Units.size() > m_unitsData.size()) {
        m_unitsData.resize(data.Units.size());
    }

    for (size_t i=0; i<data.Units.size(); i++) {
        if (data.Units[i].ID == -1) {
            continue;
        }
        m_unitsData[i] = data.Units[i];
    }

    m_taskSwapUnits.resize(10);
    for (const genie::Unit &unit : m_unitsData) {
        if (unit.Enabled && unit.Creatable.TrainLocationID > 0) {
            m_creatableUnits[unit.Creatable.TrainLocationID].push_back(&unit);
        }

        const uint8_t swapGroup = unit.Action.TaskSwapGroup;
        if (swapGroup > 0) {
            if (swapGroup >= m_taskSwapUnits.size()) {
                m_taskSwapUnits.resize(swapGroup + 1);
            }
            std::vector<const genie::Unit*> &group = m_taskSwapUnits[swapGroup];
            if (std::find_if(group.begin(), group.end(), [&](const genie::Unit *existing) { return existing->ID == unit.ID; }) != group.end()) {
                continue;
            }

            group.push_back(&unit);
        }
    }

    const std::vector<genie::Tech> &techs = DataManager::Inst().allTechs();
    for (size_t i=0; i<techs.size(); i++) {
        const genie::Tech &tech = techs.at(i);
        if (tech.ResearchLocation <= 0) {
            continue;
        }

        if (tech.Civ != -1 && tech.Civ != m_civId) {
            continue;
        }

        m_techs[i] = tech;
        m_researchAvailable[tech.ResearchLocation].push_back(&m_techs.at(i));
    }

    for (size_t i=0; i<data.Resources.size(); i++) {
        if (i >= int(genie::ResourceType::NumberOfTypes)) {
            WARN << "Too many resources" << i;
            break;
        }

        m_startingResources[genie::ResourceType(i)] = data.Resources[i];
    }
}

void Civilization::applyUnitAttributeModifier(const genie::EffectCommand &effect, int unitId)
{
    if (unitId < 0 || unitId >= m_unitsData.size()) {
        WARN << "invalid target unit" << effect.TargetUnit;
        return;
    }

    genie::Unit &unitData = m_unitsData[unitId];

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
