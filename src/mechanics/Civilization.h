#pragma once

#include "core/Types.h"
#include "core/ResourceMap.h"

#include <genie/dat/Civ.h>
#include <genie/dat/Research.h>
#include <genie/dat/TechageEffect.h>

#include <unordered_map>
#include <vector>
#include <memory>

namespace genie {
class Tech;
class Unit;
class DatFile;
}

class Civilization
{
public:
    typedef std::shared_ptr<Civilization> Ptr;
    const static genie::Unit nullUnit;

    Civilization(const int civId);

    int id() { return m_civId; }

    const std::vector<const genie::Unit *> &creatableUnits(int16_t creator) const;
    const std::vector<const genie::Tech *> &researchAvailableAt(int16_t creator) const;

    const genie::Unit &unit(const uint16_t id) const;
    const genie::Tech &tech(const uint16_t id) const;

    const std::vector<const genie::Unit *> &swappableUnits(const uint16_t taskSwapGroup) const;

    const ResourceMap &startingResources() const { return m_startingResources; }

    const std::string &name() const { return m_data.Name; }

    float startingResource(const genie::ResourceType type) const;

    const genie::Unit &unitData(unsigned id);

    void applyTechEffect(const genie::EffectCommand &effect);
    void enableUnit(const uint16_t id);
    void applyUnitAttributeModifier(const genie::EffectCommand &effect);

private:
    void applyUnitAttributeModifier(const genie::EffectCommand &effect, int unitId);

    std::unordered_map<int16_t, std::vector<const genie::Unit*>> m_creatableUnits;
    std::unordered_map<int16_t, std::vector<const genie::Tech*>> m_researchAvailable;

    std::vector<std::vector<const genie::Unit*>> m_taskSwapUnits;

    const int m_civId;
    const genie::Civ &m_data;
    std::vector<genie::Unit> m_unitsData;

    std::unordered_map<uint16_t, genie::Tech> m_techs;
    ResourceMap m_startingResources;
};


inline LogPrinter operator <<(LogPrinter os, const genie::EffectCommand::Attributes &type) {
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::EffectCommand::Attributes::";
    switch(type) {
    case genie::EffectCommand::Attributes::InvalidAttribute: os << "InvalidAttribute"; break;
    case genie::EffectCommand::Attributes::HitPoints: os << "HitPoints"; break;
    case genie::EffectCommand::Attributes::LineOfSight: os << "LineOfSight"; break;
    case genie::EffectCommand::Attributes::GarrisonCapacity: os << "GarrisonCapacity"; break;
    case genie::EffectCommand::Attributes::UnitSizeX: os << "UnitSizeX"; break;
    case genie::EffectCommand::Attributes::UnitSizeY: os << "UnitSizeY"; break;
    case genie::EffectCommand::Attributes::MovementSpeed: os << "MovementSpeed"; break;
    case genie::EffectCommand::Attributes::RotationSpeed: os << "RotationSpeed"; break;
    case genie::EffectCommand::Attributes::Armor: os << "Armor"; break;
    case genie::EffectCommand::Attributes::Attack: os << "Attack"; break;
    case genie::EffectCommand::Attributes::AttackReloadTime: os << "AttackReloadTime"; break;
    case genie::EffectCommand::Attributes::AccuracyPercent: os << "AccuracyPercent"; break;
    case genie::EffectCommand::Attributes::MaxRange: os << "MaxRange"; break;
    case genie::EffectCommand::Attributes::WorkRate: os << "WorkRate"; break;
    case genie::EffectCommand::Attributes::CarryCapacity: os << "CarryCapacity"; break;
    case genie::EffectCommand::Attributes::BaseArmor: os << "BaseArmor"; break;
    case genie::EffectCommand::Attributes::ProjectileUnit: os << "ProjectileUnit"; break;
    case genie::EffectCommand::Attributes::IconGraphicsAngle: os << "IconGraphicsAngle"; break;
    case genie::EffectCommand::Attributes::TerrainDefenseBonus: os << "TerrainDefenseBonus"; break;
    case genie::EffectCommand::Attributes::EnableSmartProjectiles: os << "EnableSmartProjectiles"; break;
    case genie::EffectCommand::Attributes::MinRange: os << "MinRange"; break;
    case genie::EffectCommand::Attributes::MainResourceStorage: os << "MainResourceStorage"; break;
    case genie::EffectCommand::Attributes::BlastWidth: os << "BlastWidth"; break;
    case genie::EffectCommand::Attributes::SearchRadius: os << "SearchRadius"; break;
    case genie::EffectCommand::Attributes::ResourceCosts: os << "ResourceCosts"; break;
    case genie::EffectCommand::Attributes::TrainTime: os << "TrainTime"; break;
    case genie::EffectCommand::Attributes::TotalMissiles: os << "TotalMissiles"; break;
    case genie::EffectCommand::Attributes::FoodCosts: os << "FoodCosts"; break;
    case genie::EffectCommand::Attributes::WoodCosts: os << "WoodCosts"; break;
    case genie::EffectCommand::Attributes::GoldCosts: os << "GoldCosts"; break;
    case genie::EffectCommand::Attributes::StoneCosts: os << "StoneCosts"; break;
    case genie::EffectCommand::Attributes::MaxTotalMissiles: os << "MaxTotalMissiles"; break;
    case genie::EffectCommand::Attributes::GarrisonHealRate: os << "GarrisonHealRate"; break;
    case genie::EffectCommand::Attributes::RegenerationRate: os << "RegenerationRate"; break;
    default: os << "Invalid"; break;
    }

    os << separator;

    os.separator = separator;

    return os;
}
