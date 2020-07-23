/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <genie/dat/ResourceType.h>
#include <unordered_map>
#include "Logger.h"

typedef std::unordered_map<genie::ResourceType, float> ResourceMap;
typedef std::pair<const genie::ResourceType, float> ResourceEntry;

inline LogPrinter operator <<(LogPrinter os, const genie::ResourceType &type) {
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::ResourceType::";
    switch(type) {
    //:%s,\(.*\) =.*,case genie::ResourceType::\1: os << "\1"; break;,
    case genie::ResourceType::InvalidResource: os << "InvalidResource"; break;
    case genie::ResourceType::FoodStorage: os << "FoodStorage"; break;
    case genie::ResourceType::WoodStorage: os << "WoodStorage"; break;
    case genie::ResourceType::StoneStorage: os << "StoneStorage"; break;
    case genie::ResourceType::GoldStorage: os << "GoldStorage"; break;
    case genie::ResourceType::PopulationHeadroom: os << "PopulationHeadroom"; break;
    case genie::ResourceType::ConversionRange: os << "ConversionRange"; break;
    case genie::ResourceType::CurrentAge: os << "CurrentAge"; break;
    case genie::ResourceType::RelicsCaptured: os << "RelicsCaptured"; break;
    case genie::ResourceType::UnusedTradeBonus: os << "UnusedTradeBonus"; break;
    case genie::ResourceType::TradeGoods: os << "TradeGoods"; break;
    case genie::ResourceType::UnusedTradeProduction: os << "UnusedTradeProduction"; break;
    case genie::ResourceType::CurrentPopulation: os << "CurrentPopulation"; break;
    case genie::ResourceType::CorpseDecayTime: os << "CorpseDecayTime"; break;
    case genie::ResourceType::RemarkableDiscovery: os << "RemarkableDiscovery"; break;
    case genie::ResourceType::MonumentsCaptured: os << "MonumentsCaptured"; break;
    case genie::ResourceType::MeatStorage: os << "MeatStorage"; break;
    case genie::ResourceType::BerryStorage: os << "BerryStorage"; break;
    case genie::ResourceType::FishStorage: os << "FishStorage"; break;
    case genie::ResourceType::Unused: os << "Unused"; break;
    case genie::ResourceType::TotalUnitsOwned: os << "TotalUnitsOwned"; break;
    case genie::ResourceType::UnitsKilled: os << "UnitsKilled"; break;
    case genie::ResourceType::TechnologyCount: os << "TechnologyCount"; break;
    case genie::ResourceType::PercentMapExplored: os << "PercentMapExplored"; break;
    case genie::ResourceType::CastleAgeTechID: os << "CastleAgeTechID"; break;
    case genie::ResourceType::ImperialAgeTechID: os << "ImperialAgeTechID"; break;
    case genie::ResourceType::FeudalAgeTechID: os << "FeudalAgeTechID"; break;
    case genie::ResourceType::AttackWarningSoundID: os << "AttackWarningSoundID"; break;
    case genie::ResourceType::EnableMonkConversion: os << "EnableMonkConversion"; break;
    case genie::ResourceType::EnableBuildingConversion: os << "EnableBuildingConversion"; break;
    case genie::ResourceType::UnusedType1: os << "UnusedType1"; break;
    case genie::ResourceType::UnusedBuildingLimit: os << "UnusedBuildingLimit"; break;
    case genie::ResourceType::UnusedFoodLimit: os << "UnusedFoodLimit"; break;
    case genie::ResourceType::BonusPopulationCap: os << "BonusPopulationCap"; break;
    case genie::ResourceType::FoodMaintenance: os << "FoodMaintenance"; break;
    case genie::ResourceType::Faith: os << "Faith"; break;
    case genie::ResourceType::FaithRechargingRate: os << "FaithRechargingRate"; break;
    case genie::ResourceType::FarmFoodAmount: os << "FarmFoodAmount"; break;
    case genie::ResourceType::CivilianPopulation: os << "CivilianPopulation"; break;
    case genie::ResourceType::UnusedType2: os << "UnusedType2"; break;
    case genie::ResourceType::AllTechsAchieved: os << "AllTechsAchieved/GoldCounter"; break;
    case genie::ResourceType::MilitaryPopulation: os << "MilitaryPopulation"; break;
    case genie::ResourceType::Conversions: os << "Conversions"; break;
    case genie::ResourceType::StandingWonders: os << "StandingWonders"; break;
    case genie::ResourceType::Razings: os << "Razings"; break;
    case genie::ResourceType::KillRatio: os << "KillRatio"; break;
    case genie::ResourceType::SurvivaltoFinish: os << "SurvivaltoFinish"; break;
    case genie::ResourceType::TributeInefficiency: os << "TributeInefficiency"; break;
    case genie::ResourceType::GoldMiningProductivity: os << "GoldMiningProductivity"; break;
    case genie::ResourceType::TownCenterUnavailable: os << "TownCenterUnavailable"; break;
    case genie::ResourceType::RevealAlly: os << "RevealAlly"; break;
    case genie::ResourceType::UnusedHouses: os << "UnusedHouses"; break;
    case genie::ResourceType::Monasteries: os << "Monasteries"; break;
    case genie::ResourceType::TributeSent: os << "TributeSent"; break;
    case genie::ResourceType::AllMonumentsCaptured: os << "AllMonumentsCaptured"; break;
    case genie::ResourceType::AllRelicsCaptured: os << "AllRelicsCaptured"; break;
    case genie::ResourceType::OreStorage: os << "OreStorage"; break;
    case genie::ResourceType::KidnapStorage: os << "KidnapStorage"; break;
    case genie::ResourceType::DarkAgeTechID: os << "DarkAgeTechID"; break;
    case genie::ResourceType::UnusedTradeGoodQuality: os << "UnusedTradeGoodQuality"; break;
    case genie::ResourceType::UnusedTradeMarketLevel: os << "UnusedTradeMarketLevel"; break;
    case genie::ResourceType::UnusedFormations: os << "UnusedFormations"; break;
    case genie::ResourceType::BuildingHousingRate: os << "BuildingHousingRate"; break;
    case genie::ResourceType::TaxGatherRate: os << "TaxGatherRate"; break;
    case genie::ResourceType::GatherAccumulator: os << "GatherAccumulator"; break;
    case genie::ResourceType::SalvageDecayRate: os << "SalvageDecayRate"; break;
    case genie::ResourceType::UnusedAllowFormations: os << "UnusedAllowFormations"; break;
    case genie::ResourceType::CanConvert: os << "CanConvert"; break;
    case genie::ResourceType::HitPointsKilled: os << "HitPointsKilled"; break;
    case genie::ResourceType::KilledP1: os << "KilledP1"; break;
    case genie::ResourceType::KilledP2: os << "KilledP2"; break;
    case genie::ResourceType::KilledP3: os << "KilledP3"; break;
    case genie::ResourceType::KilledP4: os << "KilledP4"; break;
    case genie::ResourceType::KilledP5: os << "KilledP5"; break;
    case genie::ResourceType::KilledP6: os << "KilledP6"; break;
    case genie::ResourceType::KilledP7: os << "KilledP7"; break;
    case genie::ResourceType::KilledP8: os << "KilledP8"; break;
    case genie::ResourceType::ConversionResistance: os << "ConversionResistance"; break;
    case genie::ResourceType::TradeVigRate: os << "TradeVigRate"; break;
    case genie::ResourceType::StoneMiningProductivity: os << "StoneMiningProductivity"; break;
    case genie::ResourceType::QueuedUnits: os << "QueuedUnits"; break;
    case genie::ResourceType::TrainingCount: os << "TrainingCount"; break;
    case genie::ResourceType::StartwithUnit444PTWC: os << "StartwithUnit444PTWC"; break;
    case genie::ResourceType::BoardingRechargeRate: os << "BoardingRechargeRate"; break;
    case genie::ResourceType::StartingVillagers: os << "StartingVillagers"; break;
    case genie::ResourceType::ResearchCostModifier: os << "ResearchCostModifier"; break;
    case genie::ResourceType::ResearchTimeModifier: os << "ResearchTimeModifier"; break;
    case genie::ResourceType::ConvertBoats: os << "ConvertBoats"; break;
    case genie::ResourceType::FishTrapFoodAmount: os << "FishTrapFoodAmount"; break;
    case genie::ResourceType::HealRateModifier: os << "HealRateModifier"; break;
    case genie::ResourceType::HealingRange: os << "HealingRange"; break;

    // Alpha ends here

    case genie::ResourceType::StartingFood: os << "StartingFood"; break;
    case genie::ResourceType::StartingWood: os << "StartingWood"; break;
    case genie::ResourceType::StartingStone: os << "StartingStone"; break;
    case genie::ResourceType::StartingGold: os << "StartingGold"; break;
    case genie::ResourceType::EnablePTWCKidnapLoot: os << "EnablePTWCKidnapLoot"; break;
    case genie::ResourceType::BerserkerHealTimer: os << "BerserkerHealTimer"; break;
    case genie::ResourceType::DominantSheepControl: os << "DominantSheepControl"; break;
    case genie::ResourceType::BuildingCostSum: os << "BuildingCostSum"; break;
    case genie::ResourceType::TechCostSum: os << "TechCostSum"; break;
    case genie::ResourceType::RelicIncomeSum: os << "RelicIncomeSum"; break;
    case genie::ResourceType::TradeIncomeSum: os << "TradeIncomeSum"; break;
    case genie::ResourceType::P1Tribute: os << "P1Tribute"; break;
    case genie::ResourceType::P2Tribute: os << "P2Tribute"; break;
    case genie::ResourceType::P3Tribute: os << "P3Tribute"; break;
    case genie::ResourceType::P4Tribute: os << "P4Tribute"; break;
    case genie::ResourceType::P5Tribute: os << "P5Tribute"; break;
    case genie::ResourceType::P6Tribute: os << "P6Tribute"; break;
    case genie::ResourceType::P7Tribute: os << "P7Tribute"; break;
    case genie::ResourceType::P8Tribute: os << "P8Tribute"; break;
    case genie::ResourceType::P1KillValue: os << "P1KillValue"; break;
    case genie::ResourceType::P2KillValue: os << "P2KillValue"; break;
    case genie::ResourceType::P3KillValue: os << "P3KillValue"; break;
    case genie::ResourceType::P4KillValue: os << "P4KillValue"; break;
    case genie::ResourceType::P5KillValue: os << "P5KillValue"; break;
    case genie::ResourceType::P6KillValue: os << "P6KillValue"; break;
    case genie::ResourceType::P7KillValue: os << "P7KillValue"; break;
    case genie::ResourceType::P8KillValue: os << "P8KillValue"; break;
    case genie::ResourceType::P1Razings: os << "P1Razings"; break;
    case genie::ResourceType::P2Razings: os << "P2Razings"; break;
    case genie::ResourceType::P3Razings: os << "P3Razings"; break;
    case genie::ResourceType::P4Razings: os << "P4Razings"; break;
    case genie::ResourceType::P5Razings: os << "P5Razings"; break;
    case genie::ResourceType::P6Razings: os << "P6Razings"; break;
    case genie::ResourceType::P7Razings: os << "P7Razings"; break;
    case genie::ResourceType::P8Razings: os << "P8Razings"; break;
    case genie::ResourceType::P1RazingValue: os << "P1RazingValue"; break;
    case genie::ResourceType::P2RazingValue: os << "P2RazingValue"; break;
    case genie::ResourceType::P3RazingValue: os << "P3RazingValue"; break;
    case genie::ResourceType::P4RazingValue: os << "P4RazingValue"; break;
    case genie::ResourceType::P5RazingValue: os << "P5RazingValue"; break;
    case genie::ResourceType::P6RazingValue: os << "P6RazingValue"; break;
    case genie::ResourceType::P7RazingValue: os << "P7RazingValue"; break;
    case genie::ResourceType::P8RazingValue: os << "P8RazingValue"; break;
    case genie::ResourceType::StandingCastles: os << "StandingCastles"; break;
    case genie::ResourceType::HitPointsRazed: os << "HitPointsRazed"; break;
    case genie::ResourceType::KillsbyP1: os << "KillsbyP1"; break;
    case genie::ResourceType::KillsbyP2: os << "KillsbyP2"; break;
    case genie::ResourceType::KillsbyP3: os << "KillsbyP3"; break;
    case genie::ResourceType::KillsbyP4: os << "KillsbyP4"; break;
    case genie::ResourceType::KillsbyP5: os << "KillsbyP5"; break;
    case genie::ResourceType::KillsbyP6: os << "KillsbyP6"; break;
    case genie::ResourceType::KillsbyP7: os << "KillsbyP7"; break;
    case genie::ResourceType::KillsbyP8: os << "KillsbyP8"; break;
    case genie::ResourceType::RazingsbyP1: os << "RazingsbyP1"; break;
    case genie::ResourceType::RazingsbyP2: os << "RazingsbyP2"; break;
    case genie::ResourceType::RazingsbyP3: os << "RazingsbyP3"; break;
    case genie::ResourceType::RazingsbyP4: os << "RazingsbyP4"; break;
    case genie::ResourceType::RazingsbyP5: os << "RazingsbyP5"; break;
    case genie::ResourceType::RazingsbyP6: os << "RazingsbyP6"; break;
    case genie::ResourceType::RazingsbyP7: os << "RazingsbyP7"; break;
    case genie::ResourceType::RazingsbyP8: os << "RazingsbyP8"; break;
    case genie::ResourceType::ValueKilledbyOthers: os << "ValueKilledbyOthers"; break;
    case genie::ResourceType::ValueRazedbyOthers: os << "ValueRazedbyOthers"; break;
    case genie::ResourceType::KilledbyOthers: os << "KilledbyOthers"; break;
    case genie::ResourceType::RazedbyOthers: os << "RazedbyOthers"; break;
    case genie::ResourceType::TributefromP1: os << "TributefromP1"; break;
    case genie::ResourceType::TributefromP2: os << "TributefromP2"; break;
    case genie::ResourceType::TributefromP3: os << "TributefromP3"; break;
    case genie::ResourceType::TributefromP4: os << "TributefromP4"; break;
    case genie::ResourceType::TributefromP5: os << "TributefromP5"; break;
    case genie::ResourceType::TributefromP6: os << "TributefromP6"; break;
    case genie::ResourceType::TributefromP7: os << "TributefromP7"; break;
    case genie::ResourceType::TributefromP8: os << "TributefromP8"; break;
    case genie::ResourceType::ValueCurrentUnits: os << "ValueCurrentUnits"; break;
    case genie::ResourceType::ValueCurrentBuildings: os << "ValueCurrentBuildings"; break;
    case genie::ResourceType::FoodTotal: os << "FoodTotal"; break;
    case genie::ResourceType::WoodTotal: os << "WoodTotal"; break;
    case genie::ResourceType::StoneTotal: os << "StoneTotal"; break;
    case genie::ResourceType::GoldTotal: os << "GoldTotal"; break;
    case genie::ResourceType::TotalValueofKills: os << "TotalValueofKills"; break;
    case genie::ResourceType::TotalTributeReceived: os << "TotalTributeReceived"; break;
    case genie::ResourceType::TotalValueofRazings: os << "TotalValueofRazings"; break;
    case genie::ResourceType::TotalCastlesBuilt: os << "TotalCastlesBuilt"; break;
    case genie::ResourceType::TotalWondersBuilt: os << "TotalWondersBuilt"; break;
    case genie::ResourceType::TributeScore: os << "TributeScore"; break;
    case genie::ResourceType::ConvertMinAdjustment: os << "ConvertMinAdjustment"; break;
    case genie::ResourceType::ConvertMaxAdjustment: os << "ConvertMaxAdjustment"; break;
    case genie::ResourceType::ConvertResistMinAdjustment: os << "ConvertResistMinAdjustment"; break;
    case genie::ResourceType::ConvertResistMaxAdjustment: os << "ConvertResistMaxAdjustment"; break;
    case genie::ResourceType::ConvertBuildingMin: os << "ConvertBuildingMin"; break;
    case genie::ResourceType::ConvertBuildingMax: os << "ConvertBuildingMax"; break;
    case genie::ResourceType::ConvertBuildingChance: os << "ConvertBuildingChance"; break;
    case genie::ResourceType::RevealEnemy: os << "RevealEnemy"; break;
    case genie::ResourceType::ValueWondersCastles: os << "ValueWondersCastles"; break;
    case genie::ResourceType::FoodScore: os << "FoodScore"; break;
    case genie::ResourceType::WoodScore: os << "WoodScore"; break;
    case genie::ResourceType::StoneScore: os << "StoneScore"; break;
    case genie::ResourceType::GoldScore: os << "GoldScore"; break;
    case genie::ResourceType::TCChoppingProductivity: os << "TCChoppingProductivity"; break;
    case genie::ResourceType::TCFoodGatheringProductivity: os << "TCFoodGatheringProductivity"; break;
    case genie::ResourceType::TCRelicGoldProductionRate: os << "TCRelicGoldProductionRate"; break;
    case genie::ResourceType::TCConvertedUnitsDie: os << "TCConvertedUnitsDie"; break;
    case genie::ResourceType::TCTheocracy: os << "TCTheocracy"; break;
    case genie::ResourceType::TCCrenellations: os << "TCCrenellations"; break;
    case genie::ResourceType::TCConstructionRateModifier: os << "TCConstructionRateModifier"; break;
    case genie::ResourceType::TCHunWonderBonus: os << "TCHunWonderBonus"; break;
    case genie::ResourceType::TCSpiesDiscount: os << "TCSpiesDiscount"; break;
    case genie::ResourceType::AKUnusedType3: os << "AKUnusedType3"; break;
    case genie::ResourceType::AKUnusedType4: os << "AKUnusedType4"; break;
    case genie::ResourceType::AKUnusedType5: os << "AKUnusedType5"; break;
    case genie::ResourceType::AKUnusedType6: os << "AKUnusedType6"; break;
    case genie::ResourceType::AKUnusedType7: os << "AKUnusedType7"; break;
    case genie::ResourceType::AKUnusedType8: os << "AKUnusedType8"; break;
    case genie::ResourceType::AKUnusedType9: os << "AKUnusedType9"; break;
    case genie::ResourceType::AKFeitoriaFoodProductivity: os << "AKFeitoriaFoodProductivity"; break;
    case genie::ResourceType::AKFeitoriaWoodProductivity: os << "AKFeitoriaWoodProductivity"; break;
    case genie::ResourceType::AKFeitoriaStoneProductivity: os << "AKFeitoriaStoneProductivity"; break;
    case genie::ResourceType::AKFeitoriaGoldProductivity: os << "AKFeitoriaGoldProductivity"; break;
    case genie::ResourceType::RRRevealEnemyTownCenters: os << "RRRevealEnemyTownCenters"; break;
    case genie::ResourceType::RRRelicsVisibleonMap: os << "RRRelicsVisibleonMap"; break;
    case genie::ResourceType::NumberOfTypes: os << "NumberOfTypes"; break;
    default: os << "Invalid"; break;
    }
    os << separator;

    os.separator = separator;

    return os;
}
