#pragma once

#include "core/Logger.h"
#include "gen/enums.h"

// todo: do this in generate.sh

inline LogPrinter operator <<(LogPrinter os, const ai::Age age)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::Age::";

    //:%s- \+\(.*\),.*-case ai::Age::\1: os << "\1"; break;-
    switch(age) {
    case ai::Age::DarkAge: os << "DarkAge"; break;
    case ai::Age::FeudalAge: os << "FeudalAge"; break;
    case ai::Age::CastleAge: os << "CastleAge"; break;
    case ai::Age::ImperialAge: os << "ImperialAge"; break;
    case ai::Age::PostImperialAge: os << "PostImperialAge"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::StartingResourcesType type)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::StartingResourcesType::";

    //:%s- \+\(.*\),.*-case ai::StartingResourcesType::\1: os << "\1"; break;-
    switch(type) {
    case ai::StartingResourcesType::LowResources: os << "LowResources"; break;
    case ai::StartingResourcesType::MediumResources: os << "MediumResources"; break;
    case ai::StartingResourcesType::HighResources: os << "HighResources"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::RelOp relop)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::RelOp::";

    //:%s- \+\(.*\),.*-case ai::RelOp::\1: os << "\1"; break;-
    switch(relop) {
    case ai::RelOp::LessThan: os << "LessThan"; break;
    case ai::RelOp::LessOrEqual: os << "LessOrEqual"; break;
    case ai::RelOp::GreaterThan: os << "GreaterThan"; break;
    case ai::RelOp::GreaterOrEqual: os << "GreaterOrEqual"; break;
    case ai::RelOp::Equal: os << "Equal"; break;
    case ai::RelOp::NotEqual: os << "NotEqual"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::MapSizeType mapsize)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::MapSizeType::";

    //:%s- \+\(.*\),.*-case ai::MapSizeType::\1: os << "\1"; break;-
    switch(mapsize) {
    case ai::MapSizeType::Tiny: os << "Tiny"; break;
    case ai::MapSizeType::Small: os << "Small"; break;
    case ai::MapSizeType::Medium: os << "Medium"; break;
    case ai::MapSizeType::Normal: os << "Normal"; break;
    case ai::MapSizeType::Large: os << "Large"; break;
    case ai::MapSizeType::Giant: os << "Giant"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::VictoryConditionName name)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::VictoryConditionName::";

    //:%s- \+\(.*\),.*-case ai::VictoryConditionName::\1: os << "\1"; break;-
    switch(name) {
    case ai::VictoryConditionName::Standard: os << "Standard"; break;
    case ai::VictoryConditionName::Conquest: os << "Conquest"; break;
    case ai::VictoryConditionName::TimeLimit: os << "TimeLimit"; break;
    case ai::VictoryConditionName::Score: os << "Score"; break;
    case ai::VictoryConditionName::Custom: os << "Custom"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::MapTypeName typeName)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::MapTypeName::";

    //:%s- \+\(.*\),.*-case ai::MapTypeName::\1: os << "\1"; break;-
    switch(typeName) {
    case ai::MapTypeName::Arabia: os << "Arabia"; break;
    case ai::MapTypeName::Archipelago: os << "Archipelago"; break;
    case ai::MapTypeName::Baltic: os << "Baltic"; break;
    case ai::MapTypeName::BlackForest: os << "BlackForest"; break;
    case ai::MapTypeName::Coastal: os << "Coastal"; break;
    case ai::MapTypeName::Continental: os << "Continental"; break;
    case ai::MapTypeName::CraterLake: os << "CraterLake"; break;
    case ai::MapTypeName::Fortress: os << "Fortress"; break;
    case ai::MapTypeName::GoldRush: os << "GoldRush"; break;
    case ai::MapTypeName::Highland: os << "Highland"; break;
    case ai::MapTypeName::Islands: os << "Islands"; break;
    case ai::MapTypeName::Mediterranean: os << "Mediterranean"; break;
    case ai::MapTypeName::Migration: os << "Migration"; break;
    case ai::MapTypeName::Rivers: os << "Rivers"; break;
    case ai::MapTypeName::TeamIslands: os << "TeamIslands"; break;
    case ai::MapTypeName::ScenarioMap: os << "ScenarioMap"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}


inline LogPrinter operator <<(LogPrinter os, const ai::WallType wallType)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::WallType::";

    //:%s- \+\(.*\),.*-case ai::WallType::\1: os << "\1"; break;-
    switch(wallType) {
    case ai::WallType::FortifiedWall: os << "FortifiedWall"; break;
    case ai::WallType::PalisadeWall: os << "PalisadeWall"; break;
    case ai::WallType::StoneWall: os << "StoneWall"; break;
    case ai::WallType::StoneWallLine: os << "StoneWallLine"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::Building building)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::Building::";

    //:%s- \+\(.*\),.*-case ai::Building::\1: os << "\1"; break;-
    switch(building) {
    case ai::Building::ArcheryRange: os << "ArcheryRange"; break;
    case ai::Building::Barracks: os << "Barracks"; break;
    case ai::Building::Blacksmith: os << "Blacksmith"; break;
    case ai::Building::BombardTower: os << "BombardTower"; break;
    case ai::Building::Castle: os << "Castle"; break;
    case ai::Building::Dock: os << "Dock"; break;
    case ai::Building::Farm: os << "Farm"; break;
    case ai::Building::FishTrap: os << "FishTrap"; break;
    case ai::Building::GuardTower: os << "GuardTower"; break;
    case ai::Building::House: os << "House"; break;
    case ai::Building::Keep: os << "Keep"; break;
    case ai::Building::LumberCamp: os << "LumberCamp"; break;
    case ai::Building::Market: os << "Market"; break;
    case ai::Building::Mill: os << "Mill"; break;
    case ai::Building::MiningCamp: os << "MiningCamp"; break;
    case ai::Building::Monastery: os << "Monastery"; break;
    case ai::Building::Outpost: os << "Outpost"; break;
    case ai::Building::SiegeWorkshop: os << "SiegeWorkshop"; break;
    case ai::Building::Stable: os << "Stable"; break;
    case ai::Building::TownCenter: os << "TownCenter"; break;
    case ai::Building::University: os << "University"; break;
    case ai::Building::WatchTower: os << "WatchTower"; break;
    case ai::Building::Wonder: os << "Wonder"; break;
    case ai::Building::WatchTowerLine: os << "WatchTowerLine"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::Civ civ)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::Civ::";

    //:%s- \+\(.*\),.*-case ai::Civ::\1: os << "\1"; break;-
    switch(civ) {
    case ai::Civ::Briton: os << "Briton"; break;
    case ai::Civ::Byzantine: os << "Byzantine"; break;
    case ai::Civ::Celtic: os << "Celtic"; break;
    case ai::Civ::Chinese: os << "Chinese"; break;
    case ai::Civ::Frankish: os << "Frankish"; break;
    case ai::Civ::Gothic: os << "Gothic"; break;
    case ai::Civ::Japanese: os << "Japanese"; break;
    case ai::Civ::Mongol: os << "Mongol"; break;
    case ai::Civ::Persian: os << "Persian"; break;
    case ai::Civ::Saracen: os << "Saracen"; break;
    case ai::Civ::Teutonic: os << "Teutonic"; break;
    case ai::Civ::Turkish: os << "Turkish"; break;
    case ai::Civ::Viking: os << "Viking"; break;
    case ai::Civ::MyCiv: os << "MyCiv"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::Commodity commodity)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::Commodity::";

    //:%s- \+\(.*\),.*-case ai::Commodity::\1: os << "\1"; break;-
    switch(commodity) {
    case ai::Commodity::Food: os << "Food"; break;
    case ai::Commodity::Stone: os << "Stone"; break;
    case ai::Commodity::Wood: os << "Wood"; break;
    case ai::Commodity::Gold: os << "Gold"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::DifficultyLevel difficulty)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::DifficultyLevel::";

    //:%s- \+\(.*\),.*-case ai::DifficultyLevel::\1: os << "\1"; break;-
    switch(difficulty) {
    case ai::DifficultyLevel::Easiest: os << "Easiest"; break;
    case ai::DifficultyLevel::Easy: os << "Easy"; break;
    case ai::DifficultyLevel::Moderate: os << "Moderate"; break;
    case ai::DifficultyLevel::Hard: os << "Hard"; break;
    case ai::DifficultyLevel::Hardest: os << "Hardest"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}


inline LogPrinter operator <<(LogPrinter os, const ai::DifficultyParameter param)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::DifficultyParameter::";

    //:%s- \+\(.*\),.*-case ai::DifficultyParameter::\1: os << "\1"; break;-
    switch(param) {
    case ai::DifficultyParameter::AbilityToDodgeMissiles: os << "AbilityToDodgeMissiles"; break;
    case ai::DifficultyParameter::AbilityToMaintainDistance: os << "AbilityToMaintainDistance"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}


inline LogPrinter operator <<(LogPrinter os, const ai::DiplomaticStance stance)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::DiplomaticStance::";

    //:%s- \+\(.*\),.*-case ai::DiplomaticStance::\1: os << "\1"; break;-
    switch(stance) {
    case ai::DiplomaticStance::Ally: os << "Ally"; break;
    case ai::DiplomaticStance::Neutral: os << "Neutral"; break;
    case ai::DiplomaticStance::Enemy: os << "Enemy"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}


inline LogPrinter operator <<(LogPrinter os, const ai::ActionType type)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::ActionType::";

    //:%s- \+\(.*\),.*-case ai::ActionType::\1: os << "\1"; break;-
    switch(type) {
    case ai::ActionType::AcknowledgeEvent: os << "AcknowledgeEvent"; break;
    case ai::ActionType::AcknowledgeTaunt: os << "AcknowledgeTaunt"; break;
    case ai::ActionType::AttackNow: os << "AttackNow"; break;
    case ai::ActionType::Build: os << "Build"; break;
    case ai::ActionType::BuildForward: os << "BuildForward"; break;
    case ai::ActionType::BuildGate: os << "BuildGate"; break;
    case ai::ActionType::BuildWall: os << "BuildWall"; break;
    case ai::ActionType::BuyCommodity: os << "BuyCommodity"; break;
    case ai::ActionType::CcAddResource: os << "CcAddResource"; break;
    case ai::ActionType::ChatLocal: os << "ChatLocal"; break;
    case ai::ActionType::ChatLocalToSelf: os << "ChatLocalToSelf"; break;
    case ai::ActionType::ChatLocalUsingId: os << "ChatLocalUsingId"; break;
    case ai::ActionType::ChatLocalUsingRange: os << "ChatLocalUsingRange"; break;
    case ai::ActionType::ChatToAll: os << "ChatToAll"; break;
    case ai::ActionType::ChatToAllUsingId: os << "ChatToAllUsingId"; break;
    case ai::ActionType::ChatToAllUsingRange: os << "ChatToAllUsingRange"; break;
    case ai::ActionType::ChatToAllies: os << "ChatToAllies"; break;
    case ai::ActionType::ChatToAlliesUsingId: os << "ChatToAlliesUsingId"; break;
    case ai::ActionType::ChatToAlliesUsingRange: os << "ChatToAlliesUsingRange"; break;
    case ai::ActionType::ChatToEnemies: os << "ChatToEnemies"; break;
    case ai::ActionType::ChatToEnemiesUsingId: os << "ChatToEnemiesUsingId"; break;
    case ai::ActionType::ChatToEnemiesUsingRange: os << "ChatToEnemiesUsingRange"; break;
    case ai::ActionType::ChatToPlayer: os << "ChatToPlayer"; break;
    case ai::ActionType::ChatToPlayerUsingId: os << "ChatToPlayerUsingId"; break;
    case ai::ActionType::ChatToPlayerUsingRange: os << "ChatToPlayerUsingRange"; break;
    case ai::ActionType::ChatTrace: os << "ChatTrace"; break;
    case ai::ActionType::ClearTributeMemory: os << "ClearTributeMemory"; break;
    case ai::ActionType::DeleteBuilding: os << "DeleteBuilding"; break;
    case ai::ActionType::DeleteUnit: os << "DeleteUnit"; break;
    case ai::ActionType::DisableSelf: os << "DisableSelf"; break;
    case ai::ActionType::DisableTimer: os << "DisableTimer"; break;
    case ai::ActionType::DoNothing: os << "DoNothing"; break;
    case ai::ActionType::EnableTimer: os << "EnableTimer"; break;
    case ai::ActionType::EnableWallPlacement: os << "EnableWallPlacement"; break;
    case ai::ActionType::GenerateRandomNumber: os << "GenerateRandomNumber"; break;
    case ai::ActionType::Log: os << "Log"; break;
    case ai::ActionType::LogTrace: os << "LogTrace"; break;
    case ai::ActionType::ReleaseEscrow: os << "ReleaseEscrow"; break;
    case ai::ActionType::Research: os << "Research"; break;
    case ai::ActionType::Resign: os << "Resign"; break;
    case ai::ActionType::SellCommodity: os << "SellCommodity"; break;
    case ai::ActionType::SetDifficultyParameter: os << "SetDifficultyParameter"; break;
    case ai::ActionType::SetDoctrine: os << "SetDoctrine"; break;
    case ai::ActionType::SetEscrowPercentage: os << "SetEscrowPercentage"; break;
    case ai::ActionType::SetGoal: os << "SetGoal"; break;
    case ai::ActionType::SetSharedGoal: os << "SetSharedGoal"; break;
    case ai::ActionType::SetSignal: os << "SetSignal"; break;
    case ai::ActionType::SetStance: os << "SetStance"; break;
    case ai::ActionType::SetStrategicNumber: os << "SetStrategicNumber"; break;
    case ai::ActionType::Spy: os << "Spy"; break;
    case ai::ActionType::Taunt: os << "Taunt"; break;
    case ai::ActionType::TauntUsingRange: os << "TauntUsingRange"; break;
    case ai::ActionType::Train: os << "Train"; break;
    case ai::ActionType::TributeToPlayer: os << "TributeToPlayer"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::ParameterType type)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::ParameterType::";

    //:%s- \+\(.*\),.*-case ai::ParameterType::\1: os << "\1"; break;-
    switch(type) {
    case ai::ParameterType::DarkAge: os << "DarkAge"; break;
    case ai::ParameterType::FeudalAge: os << "FeudalAge"; break;
    case ai::ParameterType::CastleAge: os << "CastleAge"; break;
    case ai::ParameterType::ImperialAge: os << "ImperialAge"; break;
    case ai::ParameterType::PostImperialAge: os << "PostImperialAge"; break;
    case ai::ParameterType::ArcheryRange: os << "ArcheryRange"; break;
    case ai::ParameterType::Barracks: os << "Barracks"; break;
    case ai::ParameterType::Blacksmith: os << "Blacksmith"; break;
    case ai::ParameterType::BombardTower: os << "BombardTower"; break;
    case ai::ParameterType::Castle: os << "Castle"; break;
    case ai::ParameterType::Dock: os << "Dock"; break;
    case ai::ParameterType::Farm: os << "Farm"; break;
    case ai::ParameterType::FishTrap: os << "FishTrap"; break;
    case ai::ParameterType::GuardTower: os << "GuardTower"; break;
    case ai::ParameterType::House: os << "House"; break;
    case ai::ParameterType::Keep: os << "Keep"; break;
    case ai::ParameterType::LumberCamp: os << "LumberCamp"; break;
    case ai::ParameterType::Market: os << "Market"; break;
    case ai::ParameterType::Mill: os << "Mill"; break;
    case ai::ParameterType::MiningCamp: os << "MiningCamp"; break;
    case ai::ParameterType::Monastery: os << "Monastery"; break;
    case ai::ParameterType::Outpost: os << "Outpost"; break;
    case ai::ParameterType::SiegeWorkshop: os << "SiegeWorkshop"; break;
    case ai::ParameterType::Stable: os << "Stable"; break;
    case ai::ParameterType::TownCenter: os << "TownCenter"; break;
    case ai::ParameterType::University: os << "University"; break;
    case ai::ParameterType::WatchTower: os << "WatchTower"; break;
    case ai::ParameterType::Wonder: os << "Wonder"; break;
    case ai::ParameterType::WatchTowerLine: os << "WatchTowerLine"; break;
    case ai::ParameterType::Briton: os << "Briton"; break;
    case ai::ParameterType::Byzantine: os << "Byzantine"; break;
    case ai::ParameterType::Celtic: os << "Celtic"; break;
    case ai::ParameterType::Chinese: os << "Chinese"; break;
    case ai::ParameterType::Frankish: os << "Frankish"; break;
    case ai::ParameterType::Gothic: os << "Gothic"; break;
    case ai::ParameterType::Japanese: os << "Japanese"; break;
    case ai::ParameterType::Mongol: os << "Mongol"; break;
    case ai::ParameterType::Persian: os << "Persian"; break;
    case ai::ParameterType::Saracen: os << "Saracen"; break;
    case ai::ParameterType::Teutonic: os << "Teutonic"; break;
    case ai::ParameterType::Turkish: os << "Turkish"; break;
    case ai::ParameterType::Viking: os << "Viking"; break;
    case ai::ParameterType::MyCiv: os << "MyCiv"; break;
    case ai::ParameterType::Food: os << "Food"; break;
    case ai::ParameterType::Stone: os << "Stone"; break;
    case ai::ParameterType::Wood: os << "Wood"; break;
    case ai::ParameterType::Gold: os << "Gold"; break;
    case ai::ParameterType::Easiest: os << "Easiest"; break;
    case ai::ParameterType::Easy: os << "Easy"; break;
    case ai::ParameterType::Moderate: os << "Moderate"; break;
    case ai::ParameterType::Hard: os << "Hard"; break;
    case ai::ParameterType::Hardest: os << "Hardest"; break;
    case ai::ParameterType::AbilityToDodgeMissiles: os << "AbilityToDodgeMissiles"; break;
    case ai::ParameterType::AbilityToMaintainDistance: os << "AbilityToMaintainDistance"; break;
    case ai::ParameterType::Ally: os << "Ally"; break;
    case ai::ParameterType::Neutral: os << "Neutral"; break;
    case ai::ParameterType::Enemy: os << "Enemy"; break;
    case ai::ParameterType::Tiny: os << "Tiny"; break;
    case ai::ParameterType::Small: os << "Small"; break;
    case ai::ParameterType::Medium: os << "Medium"; break;
    case ai::ParameterType::Normal: os << "Normal"; break;
    case ai::ParameterType::Large: os << "Large"; break;
    case ai::ParameterType::Giant: os << "Giant"; break;
    case ai::ParameterType::Arabia: os << "Arabia"; break;
    case ai::ParameterType::Archipelago: os << "Archipelago"; break;
    case ai::ParameterType::Baltic: os << "Baltic"; break;
    case ai::ParameterType::BlackForest: os << "BlackForest"; break;
    case ai::ParameterType::Coastal: os << "Coastal"; break;
    case ai::ParameterType::Continental: os << "Continental"; break;
    case ai::ParameterType::CraterLake: os << "CraterLake"; break;
    case ai::ParameterType::Fortress: os << "Fortress"; break;
    case ai::ParameterType::GoldRush: os << "GoldRush"; break;
    case ai::ParameterType::Highland: os << "Highland"; break;
    case ai::ParameterType::Islands: os << "Islands"; break;
    case ai::ParameterType::Mediterranean: os << "Mediterranean"; break;
    case ai::ParameterType::Migration: os << "Migration"; break;
    case ai::ParameterType::Rivers: os << "Rivers"; break;
    case ai::ParameterType::TeamIslands: os << "TeamIslands"; break;
    case ai::ParameterType::ScenarioMap: os << "ScenarioMap"; break;
    case ai::ParameterType::AnyAlly: os << "AnyAlly"; break;
    case ai::ParameterType::AnyComputer: os << "AnyComputer"; break;
    case ai::ParameterType::AnyComputerAlly: os << "AnyComputerAlly"; break;
    case ai::ParameterType::AnyComputerEnemy: os << "AnyComputerEnemy"; break;
    case ai::ParameterType::AnyComputerNeutral: os << "AnyComputerNeutral"; break;
    case ai::ParameterType::AnyEnemy: os << "AnyEnemy"; break;
    case ai::ParameterType::AnyHuman: os << "AnyHuman"; break;
    case ai::ParameterType::AnyHumanAlly: os << "AnyHumanAlly"; break;
    case ai::ParameterType::AnyHumanEnemy: os << "AnyHumanEnemy"; break;
    case ai::ParameterType::AnyHumanNeutral: os << "AnyHumanNeutral"; break;
    case ai::ParameterType::AnyNeutral: os << "AnyNeutral"; break;
    case ai::ParameterType::EveryAlly: os << "EveryAlly"; break;
    case ai::ParameterType::EveryComputer: os << "EveryComputer"; break;
    case ai::ParameterType::EveryEnemy: os << "EveryEnemy"; break;
    case ai::ParameterType::EveryHuman: os << "EveryHuman"; break;
    case ai::ParameterType::EveryNeutral: os << "EveryNeutral"; break;
    case ai::ParameterType::MyPlayerNumber: os << "MyPlayerNumber"; break;
    case ai::ParameterType::LessThan: os << "LessThan"; break;
    case ai::ParameterType::LessOrEqual: os << "LessOrEqual"; break;
    case ai::ParameterType::GreaterThan: os << "GreaterThan"; break;
    case ai::ParameterType::GreaterOrEqual: os << "GreaterOrEqual"; break;
    case ai::ParameterType::Equal: os << "Equal"; break;
    case ai::ParameterType::NotEqual: os << "NotEqual"; break;
    case ai::ParameterType::RiArbalest: os << "RiArbalest"; break;
    case ai::ParameterType::RiCrossbow: os << "RiCrossbow"; break;
    case ai::ParameterType::RiEliteSkirmisher: os << "RiEliteSkirmisher"; break;
    case ai::ParameterType::RiHandCannon: os << "RiHandCannon"; break;
    case ai::ParameterType::RiHeavyCavalryArcher: os << "RiHeavyCavalryArcher"; break;
    case ai::ParameterType::RiChampion: os << "RiChampion"; break;
    case ai::ParameterType::RiEliteEagleWarrior: os << "RiEliteEagleWarrior"; break;
    case ai::ParameterType::RiHalberdier: os << "RiHalberdier"; break;
    case ai::ParameterType::RiLongSwordsman: os << "RiLongSwordsman"; break;
    case ai::ParameterType::RiManAtArms: os << "RiManAtArms"; break;
    case ai::ParameterType::RiParthianTactics: os << "RiParthianTactics"; break;
    case ai::ParameterType::RiPikeman: os << "RiPikeman"; break;
    case ai::ParameterType::RiSquires: os << "RiSquires"; break;
    case ai::ParameterType::RiThumbRing: os << "RiThumbRing"; break;
    case ai::ParameterType::RiTracking: os << "RiTracking"; break;
    case ai::ParameterType::RiTwoHandedSwordsman: os << "RiTwoHandedSwordsman"; break;
    case ai::ParameterType::RiBlastFurnace: os << "RiBlastFurnace"; break;
    case ai::ParameterType::RiBodkinArrow: os << "RiBodkinArrow"; break;
    case ai::ParameterType::RiBracer: os << "RiBracer"; break;
    case ai::ParameterType::RiChainBarding: os << "RiChainBarding"; break;
    case ai::ParameterType::RiChainMail: os << "RiChainMail"; break;
    case ai::ParameterType::RiFletching: os << "RiFletching"; break;
    case ai::ParameterType::RiForging: os << "RiForging"; break;
    case ai::ParameterType::RiIronCasting: os << "RiIronCasting"; break;
    case ai::ParameterType::RiLeatherArcherArmor: os << "RiLeatherArcherArmor"; break;
    case ai::ParameterType::RiPaddedArcherArmor: os << "RiPaddedArcherArmor"; break;
    case ai::ParameterType::RiPlateBarding: os << "RiPlateBarding"; break;
    case ai::ParameterType::RiPlateMail: os << "RiPlateMail"; break;
    case ai::ParameterType::RiRingArcherArmor: os << "RiRingArcherArmor"; break;
    case ai::ParameterType::RiScaleBarding: os << "RiScaleBarding"; break;
    case ai::ParameterType::RiScaleMail: os << "RiScaleMail"; break;
    case ai::ParameterType::RiConscription: os << "RiConscription"; break;
    case ai::ParameterType::RiHoardings: os << "RiHoardings"; break;
    case ai::ParameterType::RiSappers: os << "RiSappers"; break;
    case ai::ParameterType::RiEliteBerserk: os << "RiEliteBerserk"; break;
    case ai::ParameterType::RiEliteCataphract: os << "RiEliteCataphract"; break;
    case ai::ParameterType::RiEliteChuKoNu: os << "RiEliteChuKoNu"; break;
    case ai::ParameterType::RiEliteHuskarl: os << "RiEliteHuskarl"; break;
    case ai::ParameterType::RiEliteJanissary: os << "RiEliteJanissary"; break;
    case ai::ParameterType::RiEliteLongbowman: os << "RiEliteLongbowman"; break;
    case ai::ParameterType::RiEliteMameluke: os << "RiEliteMameluke"; break;
    case ai::ParameterType::RiEliteMangudai: os << "RiEliteMangudai"; break;
    case ai::ParameterType::RiEliteSamurai: os << "RiEliteSamurai"; break;
    case ai::ParameterType::RiEliteTeutonicKnight: os << "RiEliteTeutonicKnight"; break;
    case ai::ParameterType::RiEliteThrowingAxeman: os << "RiEliteThrowingAxeman"; break;
    case ai::ParameterType::RiEliteWarElephant: os << "RiEliteWarElephant"; break;
    case ai::ParameterType::RiEliteWoadRaider: os << "RiEliteWoadRaider"; break;
    case ai::ParameterType::RiMyUniqueEliteUnit: os << "RiMyUniqueEliteUnit"; break;
    case ai::ParameterType::RiMyUniqueResearch: os << "RiMyUniqueResearch"; break;
    case ai::ParameterType::RiCannonGalleon: os << "RiCannonGalleon"; break;
    case ai::ParameterType::RiCareening: os << "RiCareening"; break;
    case ai::ParameterType::RiDeckGuns: os << "RiDeckGuns"; break;
    case ai::ParameterType::RiDryDock: os << "RiDryDock"; break;
    case ai::ParameterType::RiEliteLongboat: os << "RiEliteLongboat"; break;
    case ai::ParameterType::RiFastFireShip: os << "RiFastFireShip"; break;
    case ai::ParameterType::RiGalleon: os << "RiGalleon"; break;
    case ai::ParameterType::RiHeavyDemolitionShip: os << "RiHeavyDemolitionShip"; break;
    case ai::ParameterType::RiShipwright: os << "RiShipwright"; break;
    case ai::ParameterType::RiWarGalley: os << "RiWarGalley"; break;
    case ai::ParameterType::RiBowSaw: os << "RiBowSaw"; break;
    case ai::ParameterType::RiDoubleBitAxe: os << "RiDoubleBitAxe"; break;
    case ai::ParameterType::RiTwoManSaw: os << "RiTwoManSaw"; break;
    case ai::ParameterType::RiBanking: os << "RiBanking"; break;
    case ai::ParameterType::RiCaravan: os << "RiCaravan"; break;
    case ai::ParameterType::RiCartography: os << "RiCartography"; break;
    case ai::ParameterType::RiCoinage: os << "RiCoinage"; break;
    case ai::ParameterType::RiGuilds: os << "RiGuilds"; break;
    case ai::ParameterType::RiCropRotation: os << "RiCropRotation"; break;
    case ai::ParameterType::RiHeavyPlow: os << "RiHeavyPlow"; break;
    case ai::ParameterType::RiHorseCollar: os << "RiHorseCollar"; break;
    case ai::ParameterType::RiGoldMining: os << "RiGoldMining"; break;
    case ai::ParameterType::RiGoldShaftMining: os << "RiGoldShaftMining"; break;
    case ai::ParameterType::RiStoneMining: os << "RiStoneMining"; break;
    case ai::ParameterType::RiStoneShaftMining: os << "RiStoneShaftMining"; break;
    case ai::ParameterType::RiAtonement: os << "RiAtonement"; break;
    case ai::ParameterType::RiBlockPrinting: os << "RiBlockPrinting"; break;
    case ai::ParameterType::RiFaith: os << "RiFaith"; break;
    case ai::ParameterType::RiFervor: os << "RiFervor"; break;
    case ai::ParameterType::RiHerbalMedicine: os << "RiHerbalMedicine"; break;
    case ai::ParameterType::RiHeresy: os << "RiHeresy"; break;
    case ai::ParameterType::RiIllumination: os << "RiIllumination"; break;
    case ai::ParameterType::RiRedemption: os << "RiRedemption"; break;
    case ai::ParameterType::RiSanctity: os << "RiSanctity"; break;
    case ai::ParameterType::RiTheocracy: os << "RiTheocracy"; break;
    case ai::ParameterType::RiBombardCannon: os << "RiBombardCannon"; break;
    case ai::ParameterType::RiCappedRam: os << "RiCappedRam"; break;
    case ai::ParameterType::RiHeavyScorpion: os << "RiHeavyScorpion"; break;
    case ai::ParameterType::RiOnager: os << "RiOnager"; break;
    case ai::ParameterType::RiScorpion: os << "RiScorpion"; break;
    case ai::ParameterType::RiSiegeOnager: os << "RiSiegeOnager"; break;
    case ai::ParameterType::RiSiegeRam: os << "RiSiegeRam"; break;
    case ai::ParameterType::RiBloodlines: os << "RiBloodlines"; break;
    case ai::ParameterType::RiCavalier: os << "RiCavalier"; break;
    case ai::ParameterType::RiHeavyCamel: os << "RiHeavyCamel"; break;
    case ai::ParameterType::RiHusbandry: os << "RiHusbandry"; break;
    case ai::ParameterType::RiHussar: os << "RiHussar"; break;
    case ai::ParameterType::RiLightCavalry: os << "RiLightCavalry"; break;
    case ai::ParameterType::RiPaladin: os << "RiPaladin"; break;
    case ai::ParameterType::RiHandCart: os << "RiHandCart"; break;
    case ai::ParameterType::RiLoom: os << "RiLoom"; break;
    case ai::ParameterType::RiTownPatrol: os << "RiTownPatrol"; break;
    case ai::ParameterType::RiTownWatch: os << "RiTownWatch"; break;
    case ai::ParameterType::RiWheelBarrow: os << "RiWheelBarrow"; break;
    case ai::ParameterType::RiArchitecture: os << "RiArchitecture"; break;
    case ai::ParameterType::RiBallistics: os << "RiBallistics"; break;
    case ai::ParameterType::RiBombardTower: os << "RiBombardTower"; break;
    case ai::ParameterType::RiChemistry: os << "RiChemistry"; break;
    case ai::ParameterType::RiFortifiedWall: os << "RiFortifiedWall"; break;
    case ai::ParameterType::RiGuardTower: os << "RiGuardTower"; break;
    case ai::ParameterType::RiHeatedShot: os << "RiHeatedShot"; break;
    case ai::ParameterType::RiKeep: os << "RiKeep"; break;
    case ai::ParameterType::RiMasonry: os << "RiMasonry"; break;
    case ai::ParameterType::RiMurderHoles: os << "RiMurderHoles"; break;
    case ai::ParameterType::RiSiegeEngineers: os << "RiSiegeEngineers"; break;
    case ai::ParameterType::RiStonecutting: os << "RiStonecutting"; break;
    case ai::ParameterType::MyUniqueUnitUpgrade: os << "MyUniqueUnitUpgrade"; break;
    case ai::ParameterType::MyUniqueResearch: os << "MyUniqueResearch"; break;
    case ai::ParameterType::LowResources: os << "LowResources"; break;
    case ai::ParameterType::MediumResources: os << "MediumResources"; break;
    case ai::ParameterType::HighResources: os << "HighResources"; break;
    case ai::ParameterType::SnPercentCivilianExplorers: os << "SnPercentCivilianExplorers"; break;
    case ai::ParameterType::SnPercentCivilianBuilders: os << "SnPercentCivilianBuilders"; break;
    case ai::ParameterType::SnPercentCivilianGatherers: os << "SnPercentCivilianGatherers"; break;
    case ai::ParameterType::SnCapCivilianExplorers: os << "SnCapCivilianExplorers"; break;
    case ai::ParameterType::SnCapCivilianBuilders: os << "SnCapCivilianBuilders"; break;
    case ai::ParameterType::SnCapCivilianGatherers: os << "SnCapCivilianGatherers"; break;
    case ai::ParameterType::SnMinimumAttackGroupSize: os << "SnMinimumAttackGroupSize"; break;
    case ai::ParameterType::SnTotalNumberExplorers: os << "SnTotalNumberExplorers"; break;
    case ai::ParameterType::SnPercentEnemySightedResponse: os << "SnPercentEnemySightedResponse"; break;
    case ai::ParameterType::SnEnemySightedResponseDistance: os << "SnEnemySightedResponseDistance"; break;
    case ai::ParameterType::SnSentryDistance: os << "SnSentryDistance"; break;
    case ai::ParameterType::SnRelicReturnDistance: os << "SnRelicReturnDistance"; break;
    case ai::ParameterType::SnMinimumDefendGroupSize: os << "SnMinimumDefendGroupSize"; break;
    case ai::ParameterType::SnMaximumAttackGroupSize: os << "SnMaximumAttackGroupSize"; break;
    case ai::ParameterType::SnMaximumDefendGroupSize: os << "SnMaximumDefendGroupSize"; break;
    case ai::ParameterType::SnMinimumPeaceLikeLevel: os << "SnMinimumPeaceLikeLevel"; break;
    case ai::ParameterType::SnPercentExplorationRequired: os << "SnPercentExplorationRequired"; break;
    case ai::ParameterType::SnZeroPriorityDistance: os << "SnZeroPriorityDistance"; break;
    case ai::ParameterType::SnMinimumCivilianExplorers: os << "SnMinimumCivilianExplorers"; break;
    case ai::ParameterType::SnNumberAttackGroups: os << "SnNumberAttackGroups"; break;
    case ai::ParameterType::SnNumberDefendGroups: os << "SnNumberDefendGroups"; break;
    case ai::ParameterType::SnAttackGroupGatherSpacing: os << "SnAttackGroupGatherSpacing"; break;
    case ai::ParameterType::SnNumberExploreGroups: os << "SnNumberExploreGroups"; break;
    case ai::ParameterType::SnMinimumExploreGroupSize: os << "SnMinimumExploreGroupSize"; break;
    case ai::ParameterType::SnMaximumExploreGroupSize: os << "SnMaximumExploreGroupSize"; break;
    case ai::ParameterType::SnGoldDefendPriority: os << "SnGoldDefendPriority"; break;
    case ai::ParameterType::SnStoneDefendPriority: os << "SnStoneDefendPriority"; break;
    case ai::ParameterType::SnForageDefendPriority: os << "SnForageDefendPriority"; break;
    case ai::ParameterType::SnRelicDefendPriority: os << "SnRelicDefendPriority"; break;
    case ai::ParameterType::SnTownDefendPriority: os << "SnTownDefendPriority"; break;
    case ai::ParameterType::SnDefenseDistance: os << "SnDefenseDistance"; break;
    case ai::ParameterType::SnNumberBoatAttackGroups: os << "SnNumberBoatAttackGroups"; break;
    case ai::ParameterType::SnMinimumBoatAttackGroupSize: os << "SnMinimumBoatAttackGroupSize"; break;
    case ai::ParameterType::SnMaximumBoatAttackGroupSize: os << "SnMaximumBoatAttackGroupSize"; break;
    case ai::ParameterType::SnNumberBoatExploreGroups: os << "SnNumberBoatExploreGroups"; break;
    case ai::ParameterType::SnMinimumBoatExploreGroupSize: os << "SnMinimumBoatExploreGroupSize"; break;
    case ai::ParameterType::SnMaximumBoatExploreGroupSize: os << "SnMaximumBoatExploreGroupSize"; break;
    case ai::ParameterType::SnNumberBoatDefendGroups: os << "SnNumberBoatDefendGroups"; break;
    case ai::ParameterType::SnMinimumBoatDefendGroupSize: os << "SnMinimumBoatDefendGroupSize"; break;
    case ai::ParameterType::SnMaximumBoatDefendGroupSize: os << "SnMaximumBoatDefendGroupSize"; break;
    case ai::ParameterType::SnDockDefendPriority: os << "SnDockDefendPriority"; break;
    case ai::ParameterType::SnSentryDistanceVariation: os << "SnSentryDistanceVariation"; break;
    case ai::ParameterType::SnMinimumTownSize: os << "SnMinimumTownSize"; break;
    case ai::ParameterType::SnMaximumTownSize: os << "SnMaximumTownSize"; break;
    case ai::ParameterType::SnGroupCommanderSelectionMethod: os << "SnGroupCommanderSelectionMethod"; break;
    case ai::ParameterType::SnConsecutiveIdleUnitLimit: os << "SnConsecutiveIdleUnitLimit"; break;
    case ai::ParameterType::SnTargetEvaluationDistance: os << "SnTargetEvaluationDistance"; break;
    case ai::ParameterType::SnTargetEvaluationHitpoints: os << "SnTargetEvaluationHitpoints"; break;
    case ai::ParameterType::SnTargetEvaluationDamageCapability: os << "SnTargetEvaluationDamageCapability"; break;
    case ai::ParameterType::SnTargetEvaluationKills: os << "SnTargetEvaluationKills"; break;
    case ai::ParameterType::SnTargetEvaluationAllyProximity: os << "SnTargetEvaluationAllyProximity"; break;
    case ai::ParameterType::SnTargetEvaluationRof: os << "SnTargetEvaluationRof"; break;
    case ai::ParameterType::SnTargetEvaluationRandomness: os << "SnTargetEvaluationRandomness"; break;
    case ai::ParameterType::SnCampMaxDistance: os << "SnCampMaxDistance"; break;
    case ai::ParameterType::SnMillMaxDistance: os << "SnMillMaxDistance"; break;
    case ai::ParameterType::SnTargetEvaluationAttackAttempts: os << "SnTargetEvaluationAttackAttempts"; break;
    case ai::ParameterType::SnTargetEvaluationRange: os << "SnTargetEvaluationRange"; break;
    case ai::ParameterType::SnDefendOverlapDistance: os << "SnDefendOverlapDistance"; break;
    case ai::ParameterType::SnScaleMinimumAttackGroupSize: os << "SnScaleMinimumAttackGroupSize"; break;
    case ai::ParameterType::SnScaleMaximumAttackGroupSize: os << "SnScaleMaximumAttackGroupSize"; break;
    case ai::ParameterType::SnAttackGroupSizeRandomness: os << "SnAttackGroupSizeRandomness"; break;
    case ai::ParameterType::SnScalingFrequency: os << "SnScalingFrequency"; break;
    case ai::ParameterType::SnMaximumGaiaAttackResponse: os << "SnMaximumGaiaAttackResponse"; break;
    case ai::ParameterType::SnBuildFrequency: os << "SnBuildFrequency"; break;
    case ai::ParameterType::SnAttackSeparationTimeRandomness: os << "SnAttackSeparationTimeRandomness"; break;
    case ai::ParameterType::SnAttackIntelligence: os << "SnAttackIntelligence"; break;
    case ai::ParameterType::SnInitialAttackDelay: os << "SnInitialAttackDelay"; break;
    case ai::ParameterType::SnSaveScenarioInformation: os << "SnSaveScenarioInformation"; break;
    case ai::ParameterType::SnSpecialAttackType1: os << "SnSpecialAttackType1"; break;
    case ai::ParameterType::SnSpecialAttackInfluence1: os << "SnSpecialAttackInfluence1"; break;
    case ai::ParameterType::SnMinimumWaterBodySizeForDock: os << "SnMinimumWaterBodySizeForDock"; break;
    case ai::ParameterType::SnNumberBuildAttemptsBeforeSkip: os << "SnNumberBuildAttemptsBeforeSkip"; break;
    case ai::ParameterType::SnMaxSkipsPerAttempt: os << "SnMaxSkipsPerAttempt"; break;
    case ai::ParameterType::SnFoodGathererPercentage: os << "SnFoodGathererPercentage"; break;
    case ai::ParameterType::SnGoldGathererPercentage: os << "SnGoldGathererPercentage"; break;
    case ai::ParameterType::SnStoneGathererPercentage: os << "SnStoneGathererPercentage"; break;
    case ai::ParameterType::SnWoodGathererPercentage: os << "SnWoodGathererPercentage"; break;
    case ai::ParameterType::SnTargetEvaluationContinent: os << "SnTargetEvaluationContinent"; break;
    case ai::ParameterType::SnTargetEvaluationSiegeWeapon: os << "SnTargetEvaluationSiegeWeapon"; break;
    case ai::ParameterType::SnGroupLeaderDefenseDistance: os << "SnGroupLeaderDefenseDistance"; break;
    case ai::ParameterType::SnInitialAttackDelayType: os << "SnInitialAttackDelayType"; break;
    case ai::ParameterType::SnBlotExplorationMap: os << "SnBlotExplorationMap"; break;
    case ai::ParameterType::SnBlotSize: os << "SnBlotSize"; break;
    case ai::ParameterType::SnIntelligentGathering: os << "SnIntelligentGathering"; break;
    case ai::ParameterType::SnTaskUngroupedSoldiers: os << "SnTaskUngroupedSoldiers"; break;
    case ai::ParameterType::SnTargetEvaluationBoat: os << "SnTargetEvaluationBoat"; break;
    case ai::ParameterType::SnNumberEnemyObjectsRequired: os << "SnNumberEnemyObjectsRequired"; break;
    case ai::ParameterType::SnNumberMaxSkipCycles: os << "SnNumberMaxSkipCycles"; break;
    case ai::ParameterType::SnRetaskGatherAmount: os << "SnRetaskGatherAmount"; break;
    case ai::ParameterType::SnMaxRetaskGatherAmount: os << "SnMaxRetaskGatherAmount"; break;
    case ai::ParameterType::SnMaxBuildPlanGathererPercentage: os << "SnMaxBuildPlanGathererPercentage"; break;
    case ai::ParameterType::SnFoodDropsiteDistance: os << "SnFoodDropsiteDistance"; break;
    case ai::ParameterType::SnWoodDropsiteDistance: os << "SnWoodDropsiteDistance"; break;
    case ai::ParameterType::SnStoneDropsiteDistance: os << "SnStoneDropsiteDistance"; break;
    case ai::ParameterType::SnGoldDropsiteDistance: os << "SnGoldDropsiteDistance"; break;
    case ai::ParameterType::SnInitialExplorationRequired: os << "SnInitialExplorationRequired"; break;
    case ai::ParameterType::SnRandomPlacementFactor: os << "SnRandomPlacementFactor"; break;
    case ai::ParameterType::SnRequiredForestTiles: os << "SnRequiredForestTiles"; break;
    case ai::ParameterType::SnAttackDiplomacyImpact: os << "SnAttackDiplomacyImpact"; break;
    case ai::ParameterType::SnPercentHalfExploration: os << "SnPercentHalfExploration"; break;
    case ai::ParameterType::SnTargetEvaluationTimeKillRatio: os << "SnTargetEvaluationTimeKillRatio"; break;
    case ai::ParameterType::SnTargetEvaluationInProgress: os << "SnTargetEvaluationInProgress"; break;
    case ai::ParameterType::SnAttackWinningPlayer: os << "SnAttackWinningPlayer"; break;
    case ai::ParameterType::SnCoopShareInformation: os << "SnCoopShareInformation"; break;
    case ai::ParameterType::SnAttackWinningPlayerFactor: os << "SnAttackWinningPlayerFactor"; break;
    case ai::ParameterType::SnCoopShareAttacking: os << "SnCoopShareAttacking"; break;
    case ai::ParameterType::SnCoopShareAttackingInterval: os << "SnCoopShareAttackingInterval"; break;
    case ai::ParameterType::SnPercentageExploreExterminators: os << "SnPercentageExploreExterminators"; break;
    case ai::ParameterType::SnTrackPlayerHistory: os << "SnTrackPlayerHistory"; break;
    case ai::ParameterType::SnMinimumDropsiteBuffer: os << "SnMinimumDropsiteBuffer"; break;
    case ai::ParameterType::SnUseByTypeMaxGathering: os << "SnUseByTypeMaxGathering"; break;
    case ai::ParameterType::SnMinimumBoarHuntGroupSize: os << "SnMinimumBoarHuntGroupSize"; break;
    case ai::ParameterType::SnMinimumAmountForTrading: os << "SnMinimumAmountForTrading"; break;
    case ai::ParameterType::SnEasiestReactionPercentage: os << "SnEasiestReactionPercentage"; break;
    case ai::ParameterType::SnEasierReactionPercentage: os << "SnEasierReactionPercentage"; break;
    case ai::ParameterType::SnHitsBeforeAllianceChange: os << "SnHitsBeforeAllianceChange"; break;
    case ai::ParameterType::SnAllowCivilianDefense: os << "SnAllowCivilianDefense"; break;
    case ai::ParameterType::SnNumberForwardBuilders: os << "SnNumberForwardBuilders"; break;
    case ai::ParameterType::SnPercentAttackSoldiers: os << "SnPercentAttackSoldiers"; break;
    case ai::ParameterType::SnPercentAttackBoats: os << "SnPercentAttackBoats"; break;
    case ai::ParameterType::SnDoNotScaleForDifficultyLevel: os << "SnDoNotScaleForDifficultyLevel"; break;
    case ai::ParameterType::SnGroupFormDistance: os << "SnGroupFormDistance"; break;
    case ai::ParameterType::SnIgnoreAttackGroupUnderAttack: os << "SnIgnoreAttackGroupUnderAttack"; break;
    case ai::ParameterType::SnGatherDefenseUnits: os << "SnGatherDefenseUnits"; break;
    case ai::ParameterType::SnMaximumWoodDropDistance: os << "SnMaximumWoodDropDistance"; break;
    case ai::ParameterType::SnMaximumFoodDropDistance: os << "SnMaximumFoodDropDistance"; break;
    case ai::ParameterType::SnMaximumHuntDropDistance: os << "SnMaximumHuntDropDistance"; break;
    case ai::ParameterType::SnMaximumFishBoatDropDistance: os << "SnMaximumFishBoatDropDistance"; break;
    case ai::ParameterType::SnMaximumGoldDropDistance: os << "SnMaximumGoldDropDistance"; break;
    case ai::ParameterType::SnMaximumStoneDropDistance: os << "SnMaximumStoneDropDistance"; break;
    case ai::ParameterType::SnGatherIdleSoldiersAtCenter: os << "SnGatherIdleSoldiersAtCenter"; break;
    case ai::ParameterType::SnGarrisonRams: os << "SnGarrisonRams"; break;
    case ai::ParameterType::Arbalest: os << "Arbalest"; break;
    case ai::ParameterType::Archer: os << "Archer"; break;
    case ai::ParameterType::CavalryArcher: os << "CavalryArcher"; break;
    case ai::ParameterType::Crossbowman: os << "Crossbowman"; break;
    case ai::ParameterType::EliteSkirmisher: os << "EliteSkirmisher"; break;
    case ai::ParameterType::HandCannoneer: os << "HandCannoneer"; break;
    case ai::ParameterType::HeavyCavalryArcher: os << "HeavyCavalryArcher"; break;
    case ai::ParameterType::Skirmisher: os << "Skirmisher"; break;
    case ai::ParameterType::Champion: os << "Champion"; break;
    case ai::ParameterType::EagleWarrior: os << "EagleWarrior"; break;
    case ai::ParameterType::EliteEagleWarrior: os << "EliteEagleWarrior"; break;
    case ai::ParameterType::Halberdier: os << "Halberdier"; break;
    case ai::ParameterType::LongSwordsman: os << "LongSwordsman"; break;
    case ai::ParameterType::ManAtArms: os << "ManAtArms"; break;
    case ai::ParameterType::Militiaman: os << "Militiaman"; break;
    case ai::ParameterType::Pikeman: os << "Pikeman"; break;
    case ai::ParameterType::Spearman: os << "Spearman"; break;
    case ai::ParameterType::TwoHandedSwordsman: os << "TwoHandedSwordsman"; break;
    case ai::ParameterType::Berserk: os << "Berserk"; break;
    case ai::ParameterType::Cataphract: os << "Cataphract"; break;
    case ai::ParameterType::ChuKoNu: os << "ChuKoNu"; break;
    case ai::ParameterType::Conquistador: os << "Conquistador"; break;
    case ai::ParameterType::EliteBerserk: os << "EliteBerserk"; break;
    case ai::ParameterType::EliteCataphract: os << "EliteCataphract"; break;
    case ai::ParameterType::EliteChuKoNu: os << "EliteChuKoNu"; break;
    case ai::ParameterType::EliteConquistador: os << "EliteConquistador"; break;
    case ai::ParameterType::EliteHuskarl: os << "EliteHuskarl"; break;
    case ai::ParameterType::EliteJaguarWarrior: os << "EliteJaguarWarrior"; break;
    case ai::ParameterType::EliteJanissary: os << "EliteJanissary"; break;
    case ai::ParameterType::EliteLongbowman: os << "EliteLongbowman"; break;
    case ai::ParameterType::EliteMameluke: os << "EliteMameluke"; break;
    case ai::ParameterType::EliteMangudai: os << "EliteMangudai"; break;
    case ai::ParameterType::ElitePlumedArcher: os << "ElitePlumedArcher"; break;
    case ai::ParameterType::EliteSamurai: os << "EliteSamurai"; break;
    case ai::ParameterType::EliteTarkan: os << "EliteTarkan"; break;
    case ai::ParameterType::EliteTeutonicKnight: os << "EliteTeutonicKnight"; break;
    case ai::ParameterType::EliteThrowingAxeman: os << "EliteThrowingAxeman"; break;
    case ai::ParameterType::EliteWarElephant: os << "EliteWarElephant"; break;
    case ai::ParameterType::EliteWarWagon: os << "EliteWarWagon"; break;
    case ai::ParameterType::EliteWoadRaider: os << "EliteWoadRaider"; break;
    case ai::ParameterType::Huskarl: os << "Huskarl"; break;
    case ai::ParameterType::JaguarWarrior: os << "JaguarWarrior"; break;
    case ai::ParameterType::Janissary: os << "Janissary"; break;
    case ai::ParameterType::Longbowman: os << "Longbowman"; break;
    case ai::ParameterType::Mameluke: os << "Mameluke"; break;
    case ai::ParameterType::Mangudai: os << "Mangudai"; break;
    case ai::ParameterType::Petard: os << "Petard"; break;
    case ai::ParameterType::PlumedArcher: os << "PlumedArcher"; break;
    case ai::ParameterType::Samurai: os << "Samurai"; break;
    case ai::ParameterType::Tarkan: os << "Tarkan"; break;
    case ai::ParameterType::TeutonicKnight: os << "TeutonicKnight"; break;
    case ai::ParameterType::ThrowingAxeman: os << "ThrowingAxeman"; break;
    case ai::ParameterType::Trebuchet: os << "Trebuchet"; break;
    case ai::ParameterType::WarElephant: os << "WarElephant"; break;
    case ai::ParameterType::WarWagon: os << "WarWagon"; break;
    case ai::ParameterType::WoadRaider: os << "WoadRaider"; break;
    case ai::ParameterType::CannonGalleon: os << "CannonGalleon"; break;
    case ai::ParameterType::DemolitionShip: os << "DemolitionShip"; break;
    case ai::ParameterType::EliteCannonGalleon: os << "EliteCannonGalleon"; break;
    case ai::ParameterType::EliteLongboat: os << "EliteLongboat"; break;
    case ai::ParameterType::EliteTurtleShip: os << "EliteTurtleShip"; break;
    case ai::ParameterType::FastFireShip: os << "FastFireShip"; break;
    case ai::ParameterType::FireShip: os << "FireShip"; break;
    case ai::ParameterType::FishingShip: os << "FishingShip"; break;
    case ai::ParameterType::Galleon: os << "Galleon"; break;
    case ai::ParameterType::Galley: os << "Galley"; break;
    case ai::ParameterType::HeavyDemolitionShip: os << "HeavyDemolitionShip"; break;
    case ai::ParameterType::Longboat: os << "Longboat"; break;
    case ai::ParameterType::TradeCog: os << "TradeCog"; break;
    case ai::ParameterType::TransportShip: os << "TransportShip"; break;
    case ai::ParameterType::TurtleShip: os << "TurtleShip"; break;
    case ai::ParameterType::WarGalley: os << "WarGalley"; break;
    case ai::ParameterType::TradeCart: os << "TradeCart"; break;
    case ai::ParameterType::Missionary: os << "Missionary"; break;
    case ai::ParameterType::Monk: os << "Monk"; break;
    case ai::ParameterType::BatteringRam: os << "BatteringRam"; break;
    case ai::ParameterType::BombardCannon: os << "BombardCannon"; break;
    case ai::ParameterType::CappedRam: os << "CappedRam"; break;
    case ai::ParameterType::HeavyScorpion: os << "HeavyScorpion"; break;
    case ai::ParameterType::Mangonel: os << "Mangonel"; break;
    case ai::ParameterType::Onager: os << "Onager"; break;
    case ai::ParameterType::Scorpion: os << "Scorpion"; break;
    case ai::ParameterType::SiegeOnager: os << "SiegeOnager"; break;
    case ai::ParameterType::SiegeRam: os << "SiegeRam"; break;
    case ai::ParameterType::Camel: os << "Camel"; break;
    case ai::ParameterType::Cavalier: os << "Cavalier"; break;
    case ai::ParameterType::HeavyCamel: os << "HeavyCamel"; break;
    case ai::ParameterType::Hussar: os << "Hussar"; break;
    case ai::ParameterType::Knight: os << "Knight"; break;
    case ai::ParameterType::LightCavalry: os << "LightCavalry"; break;
    case ai::ParameterType::Paladin: os << "Paladin"; break;
    case ai::ParameterType::ScoutCavalry: os << "ScoutCavalry"; break;
    case ai::ParameterType::Villager: os << "Villager"; break;
    case ai::ParameterType::ArcherLine: os << "ArcherLine"; break;
    case ai::ParameterType::CavalryArcherLine: os << "CavalryArcherLine"; break;
    case ai::ParameterType::SkirmisherLine: os << "SkirmisherLine"; break;
    case ai::ParameterType::EagleWarriorLine: os << "EagleWarriorLine"; break;
    case ai::ParameterType::MilitiamanLine: os << "MilitiamanLine"; break;
    case ai::ParameterType::SpearmanLine: os << "SpearmanLine"; break;
    case ai::ParameterType::BerserkLine: os << "BerserkLine"; break;
    case ai::ParameterType::CataphractLine: os << "CataphractLine"; break;
    case ai::ParameterType::ChuKoNuLine: os << "ChuKoNuLine"; break;
    case ai::ParameterType::ConquistadorLine: os << "ConquistadorLine"; break;
    case ai::ParameterType::HuskarlLine: os << "HuskarlLine"; break;
    case ai::ParameterType::JaguarWarriorLine: os << "JaguarWarriorLine"; break;
    case ai::ParameterType::JanissaryLine: os << "JanissaryLine"; break;
    case ai::ParameterType::LongbowmanLine: os << "LongbowmanLine"; break;
    case ai::ParameterType::MamelukeLine: os << "MamelukeLine"; break;
    case ai::ParameterType::MangudaiLine: os << "MangudaiLine"; break;
    case ai::ParameterType::PlumedArcherLine: os << "PlumedArcherLine"; break;
    case ai::ParameterType::SamuraiLine: os << "SamuraiLine"; break;
    case ai::ParameterType::TarkanLine: os << "TarkanLine"; break;
    case ai::ParameterType::TeutonicKnightLine: os << "TeutonicKnightLine"; break;
    case ai::ParameterType::ThrowingAxemanLine: os << "ThrowingAxemanLine"; break;
    case ai::ParameterType::WarElephantLine: os << "WarElephantLine"; break;
    case ai::ParameterType::WarWagonLine: os << "WarWagonLine"; break;
    case ai::ParameterType::WoadRaiderLine: os << "WoadRaiderLine"; break;
    case ai::ParameterType::CannonGalleonLine: os << "CannonGalleonLine"; break;
    case ai::ParameterType::DemolitionShipLine: os << "DemolitionShipLine"; break;
    case ai::ParameterType::FireShipLine: os << "FireShipLine"; break;
    case ai::ParameterType::GalleyLine: os << "GalleyLine"; break;
    case ai::ParameterType::LongboatLine: os << "LongboatLine"; break;
    case ai::ParameterType::TurtleShipLine: os << "TurtleShipLine"; break;
    case ai::ParameterType::BatteringRamLine: os << "BatteringRamLine"; break;
    case ai::ParameterType::MangonelLine: os << "MangonelLine"; break;
    case ai::ParameterType::ScorpionLine: os << "ScorpionLine"; break;
    case ai::ParameterType::CamelLine: os << "CamelLine"; break;
    case ai::ParameterType::KnightLine: os << "KnightLine"; break;
    case ai::ParameterType::ScoutCavalryLine: os << "ScoutCavalryLine"; break;
    case ai::ParameterType::MyEliteUniqueUnit: os << "MyEliteUniqueUnit"; break;
    case ai::ParameterType::MyUniqueUnit: os << "MyUniqueUnit"; break;
    case ai::ParameterType::MyUniqueUnitLine: os << "MyUniqueUnitLine"; break;
    case ai::ParameterType::Standard: os << "Standard"; break;
    case ai::ParameterType::Conquest: os << "Conquest"; break;
    case ai::ParameterType::TimeLimit: os << "TimeLimit"; break;
    case ai::ParameterType::Score: os << "Score"; break;
    case ai::ParameterType::Custom: os << "Custom"; break;
    case ai::ParameterType::FortifiedWall: os << "FortifiedWall"; break;
    case ai::ParameterType::PalisadeWall: os << "PalisadeWall"; break;
    case ai::ParameterType::StoneWall: os << "StoneWall"; break;
    case ai::ParameterType::StoneWallLine: os << "StoneWallLine"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::ResearchItem research)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::ResearchItem::";

    //:%s- \+\(.*\),.*-case ai::ResearchItem::\1: os << "\1"; break;-
    switch(research) {
    case ai::ResearchItem::RiArbalest: os << "RiArbalest"; break;
    case ai::ResearchItem::RiCrossbow: os << "RiCrossbow"; break;
    case ai::ResearchItem::RiEliteSkirmisher: os << "RiEliteSkirmisher"; break;
    case ai::ResearchItem::RiHandCannon: os << "RiHandCannon"; break;
    case ai::ResearchItem::RiHeavyCavalryArcher: os << "RiHeavyCavalryArcher"; break;
    case ai::ResearchItem::RiChampion: os << "RiChampion"; break;
    case ai::ResearchItem::RiEliteEagleWarrior: os << "RiEliteEagleWarrior"; break;
    case ai::ResearchItem::RiHalberdier: os << "RiHalberdier"; break;
    case ai::ResearchItem::RiLongSwordsman: os << "RiLongSwordsman"; break;
    case ai::ResearchItem::RiManAtArms: os << "RiManAtArms"; break;
    case ai::ResearchItem::RiParthianTactics: os << "RiParthianTactics"; break;
    case ai::ResearchItem::RiPikeman: os << "RiPikeman"; break;
    case ai::ResearchItem::RiSquires: os << "RiSquires"; break;
    case ai::ResearchItem::RiThumbRing: os << "RiThumbRing"; break;
    case ai::ResearchItem::RiTracking: os << "RiTracking"; break;
    case ai::ResearchItem::RiTwoHandedSwordsman: os << "RiTwoHandedSwordsman"; break;
    case ai::ResearchItem::RiBlastFurnace: os << "RiBlastFurnace"; break;
    case ai::ResearchItem::RiBodkinArrow: os << "RiBodkinArrow"; break;
    case ai::ResearchItem::RiBracer: os << "RiBracer"; break;
    case ai::ResearchItem::RiChainBarding: os << "RiChainBarding"; break;
    case ai::ResearchItem::RiChainMail: os << "RiChainMail"; break;
    case ai::ResearchItem::RiFletching: os << "RiFletching"; break;
    case ai::ResearchItem::RiForging: os << "RiForging"; break;
    case ai::ResearchItem::RiIronCasting: os << "RiIronCasting"; break;
    case ai::ResearchItem::RiLeatherArcherArmor: os << "RiLeatherArcherArmor"; break;
    case ai::ResearchItem::RiPaddedArcherArmor: os << "RiPaddedArcherArmor"; break;
    case ai::ResearchItem::RiPlateBarding: os << "RiPlateBarding"; break;
    case ai::ResearchItem::RiPlateMail: os << "RiPlateMail"; break;
    case ai::ResearchItem::RiRingArcherArmor: os << "RiRingArcherArmor"; break;
    case ai::ResearchItem::RiScaleBarding: os << "RiScaleBarding"; break;
    case ai::ResearchItem::RiScaleMail: os << "RiScaleMail"; break;
    case ai::ResearchItem::RiConscription: os << "RiConscription"; break;
    case ai::ResearchItem::RiHoardings: os << "RiHoardings"; break;
    case ai::ResearchItem::RiSappers: os << "RiSappers"; break;
    case ai::ResearchItem::RiEliteBerserk: os << "RiEliteBerserk"; break;
    case ai::ResearchItem::RiEliteCataphract: os << "RiEliteCataphract"; break;
    case ai::ResearchItem::RiEliteChuKoNu: os << "RiEliteChuKoNu"; break;
    case ai::ResearchItem::RiEliteHuskarl: os << "RiEliteHuskarl"; break;
    case ai::ResearchItem::RiEliteJanissary: os << "RiEliteJanissary"; break;
    case ai::ResearchItem::RiEliteLongbowman: os << "RiEliteLongbowman"; break;
    case ai::ResearchItem::RiEliteMameluke: os << "RiEliteMameluke"; break;
    case ai::ResearchItem::RiEliteMangudai: os << "RiEliteMangudai"; break;
    case ai::ResearchItem::RiEliteSamurai: os << "RiEliteSamurai"; break;
    case ai::ResearchItem::RiEliteTeutonicKnight: os << "RiEliteTeutonicKnight"; break;
    case ai::ResearchItem::RiEliteThrowingAxeman: os << "RiEliteThrowingAxeman"; break;
    case ai::ResearchItem::RiEliteWarElephant: os << "RiEliteWarElephant"; break;
    case ai::ResearchItem::RiEliteWoadRaider: os << "RiEliteWoadRaider"; break;
    case ai::ResearchItem::RiMyUniqueEliteUnit: os << "RiMyUniqueEliteUnit"; break;
    case ai::ResearchItem::RiMyUniqueResearch: os << "RiMyUniqueResearch"; break;
    case ai::ResearchItem::RiCannonGalleon: os << "RiCannonGalleon"; break;
    case ai::ResearchItem::RiCareening: os << "RiCareening"; break;
    case ai::ResearchItem::RiDeckGuns: os << "RiDeckGuns"; break;
    case ai::ResearchItem::RiDryDock: os << "RiDryDock"; break;
    case ai::ResearchItem::RiEliteLongboat: os << "RiEliteLongboat"; break;
    case ai::ResearchItem::RiFastFireShip: os << "RiFastFireShip"; break;
    case ai::ResearchItem::RiGalleon: os << "RiGalleon"; break;
    case ai::ResearchItem::RiHeavyDemolitionShip: os << "RiHeavyDemolitionShip"; break;
    case ai::ResearchItem::RiShipwright: os << "RiShipwright"; break;
    case ai::ResearchItem::RiWarGalley: os << "RiWarGalley"; break;
    case ai::ResearchItem::RiBowSaw: os << "RiBowSaw"; break;
    case ai::ResearchItem::RiDoubleBitAxe: os << "RiDoubleBitAxe"; break;
    case ai::ResearchItem::RiTwoManSaw: os << "RiTwoManSaw"; break;
    case ai::ResearchItem::RiBanking: os << "RiBanking"; break;
    case ai::ResearchItem::RiCaravan: os << "RiCaravan"; break;
    case ai::ResearchItem::RiCartography: os << "RiCartography"; break;
    case ai::ResearchItem::RiCoinage: os << "RiCoinage"; break;
    case ai::ResearchItem::RiGuilds: os << "RiGuilds"; break;
    case ai::ResearchItem::RiCropRotation: os << "RiCropRotation"; break;
    case ai::ResearchItem::RiHeavyPlow: os << "RiHeavyPlow"; break;
    case ai::ResearchItem::RiHorseCollar: os << "RiHorseCollar"; break;
    case ai::ResearchItem::RiGoldMining: os << "RiGoldMining"; break;
    case ai::ResearchItem::RiGoldShaftMining: os << "RiGoldShaftMining"; break;
    case ai::ResearchItem::RiStoneMining: os << "RiStoneMining"; break;
    case ai::ResearchItem::RiStoneShaftMining: os << "RiStoneShaftMining"; break;
    case ai::ResearchItem::RiAtonement: os << "RiAtonement"; break;
    case ai::ResearchItem::RiBlockPrinting: os << "RiBlockPrinting"; break;
    case ai::ResearchItem::RiFaith: os << "RiFaith"; break;
    case ai::ResearchItem::RiFervor: os << "RiFervor"; break;
    case ai::ResearchItem::RiHerbalMedicine: os << "RiHerbalMedicine"; break;
    case ai::ResearchItem::RiHeresy: os << "RiHeresy"; break;
    case ai::ResearchItem::RiIllumination: os << "RiIllumination"; break;
    case ai::ResearchItem::RiRedemption: os << "RiRedemption"; break;
    case ai::ResearchItem::RiSanctity: os << "RiSanctity"; break;
    case ai::ResearchItem::RiTheocracy: os << "RiTheocracy"; break;
    case ai::ResearchItem::RiBombardCannon: os << "RiBombardCannon"; break;
    case ai::ResearchItem::RiCappedRam: os << "RiCappedRam"; break;
    case ai::ResearchItem::RiHeavyScorpion: os << "RiHeavyScorpion"; break;
    case ai::ResearchItem::RiOnager: os << "RiOnager"; break;
    case ai::ResearchItem::RiScorpion: os << "RiScorpion"; break;
    case ai::ResearchItem::RiSiegeOnager: os << "RiSiegeOnager"; break;
    case ai::ResearchItem::RiSiegeRam: os << "RiSiegeRam"; break;
    case ai::ResearchItem::RiBloodlines: os << "RiBloodlines"; break;
    case ai::ResearchItem::RiCavalier: os << "RiCavalier"; break;
    case ai::ResearchItem::RiHeavyCamel: os << "RiHeavyCamel"; break;
    case ai::ResearchItem::RiHusbandry: os << "RiHusbandry"; break;
    case ai::ResearchItem::RiHussar: os << "RiHussar"; break;
    case ai::ResearchItem::RiLightCavalry: os << "RiLightCavalry"; break;
    case ai::ResearchItem::RiPaladin: os << "RiPaladin"; break;
    case ai::ResearchItem::RiHandCart: os << "RiHandCart"; break;
    case ai::ResearchItem::RiLoom: os << "RiLoom"; break;
    case ai::ResearchItem::RiTownPatrol: os << "RiTownPatrol"; break;
    case ai::ResearchItem::RiTownWatch: os << "RiTownWatch"; break;
    case ai::ResearchItem::RiWheelBarrow: os << "RiWheelBarrow"; break;
    case ai::ResearchItem::RiArchitecture: os << "RiArchitecture"; break;
    case ai::ResearchItem::RiBallistics: os << "RiBallistics"; break;
    case ai::ResearchItem::RiBombardTower: os << "RiBombardTower"; break;
    case ai::ResearchItem::RiChemistry: os << "RiChemistry"; break;
    case ai::ResearchItem::RiFortifiedWall: os << "RiFortifiedWall"; break;
    case ai::ResearchItem::RiGuardTower: os << "RiGuardTower"; break;
    case ai::ResearchItem::RiHeatedShot: os << "RiHeatedShot"; break;
    case ai::ResearchItem::RiKeep: os << "RiKeep"; break;
    case ai::ResearchItem::RiMasonry: os << "RiMasonry"; break;
    case ai::ResearchItem::RiMurderHoles: os << "RiMurderHoles"; break;
    case ai::ResearchItem::RiSiegeEngineers: os << "RiSiegeEngineers"; break;
    case ai::ResearchItem::RiStonecutting: os << "RiStonecutting"; break;
    case ai::ResearchItem::MyUniqueUnitUpgrade: os << "MyUniqueUnitUpgrade"; break;
    case ai::ResearchItem::MyUniqueResearch: os << "MyUniqueResearch"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}


inline LogPrinter operator <<(LogPrinter os, const ai::Unit unit)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::Unit::";

    //:%s- \+\(.*\),.*-case ai::Unit::\1: os << "\1"; break;-
    switch(unit) {
    case ai::Unit::Arbalest: os << "Arbalest"; break;
    case ai::Unit::Archer: os << "Archer"; break;
    case ai::Unit::CavalryArcher: os << "CavalryArcher"; break;
    case ai::Unit::Crossbowman: os << "Crossbowman"; break;
    case ai::Unit::EliteSkirmisher: os << "EliteSkirmisher"; break;
    case ai::Unit::HandCannoneer: os << "HandCannoneer"; break;
    case ai::Unit::HeavyCavalryArcher: os << "HeavyCavalryArcher"; break;
    case ai::Unit::Skirmisher: os << "Skirmisher"; break;
    case ai::Unit::Champion: os << "Champion"; break;
    case ai::Unit::EagleWarrior: os << "EagleWarrior"; break;
    case ai::Unit::EliteEagleWarrior: os << "EliteEagleWarrior"; break;
    case ai::Unit::Halberdier: os << "Halberdier"; break;
    case ai::Unit::LongSwordsman: os << "LongSwordsman"; break;
    case ai::Unit::ManAtArms: os << "ManAtArms"; break;
    case ai::Unit::Militiaman: os << "Militiaman"; break;
    case ai::Unit::Pikeman: os << "Pikeman"; break;
    case ai::Unit::Spearman: os << "Spearman"; break;
    case ai::Unit::TwoHandedSwordsman: os << "TwoHandedSwordsman"; break;
    case ai::Unit::Berserk: os << "Berserk"; break;
    case ai::Unit::Cataphract: os << "Cataphract"; break;
    case ai::Unit::ChuKoNu: os << "ChuKoNu"; break;
    case ai::Unit::Conquistador: os << "Conquistador"; break;
    case ai::Unit::EliteBerserk: os << "EliteBerserk"; break;
    case ai::Unit::EliteCataphract: os << "EliteCataphract"; break;
    case ai::Unit::EliteChuKoNu: os << "EliteChuKoNu"; break;
    case ai::Unit::EliteConquistador: os << "EliteConquistador"; break;
    case ai::Unit::EliteHuskarl: os << "EliteHuskarl"; break;
    case ai::Unit::EliteJaguarWarrior: os << "EliteJaguarWarrior"; break;
    case ai::Unit::EliteJanissary: os << "EliteJanissary"; break;
    case ai::Unit::EliteLongbowman: os << "EliteLongbowman"; break;
    case ai::Unit::EliteMameluke: os << "EliteMameluke"; break;
    case ai::Unit::EliteMangudai: os << "EliteMangudai"; break;
    case ai::Unit::ElitePlumedArcher: os << "ElitePlumedArcher"; break;
    case ai::Unit::EliteSamurai: os << "EliteSamurai"; break;
    case ai::Unit::EliteTarkan: os << "EliteTarkan"; break;
    case ai::Unit::EliteTeutonicKnight: os << "EliteTeutonicKnight"; break;
    case ai::Unit::EliteThrowingAxeman: os << "EliteThrowingAxeman"; break;
    case ai::Unit::EliteWarElephant: os << "EliteWarElephant"; break;
    case ai::Unit::EliteWarWagon: os << "EliteWarWagon"; break;
    case ai::Unit::EliteWoadRaider: os << "EliteWoadRaider"; break;
    case ai::Unit::Huskarl: os << "Huskarl"; break;
    case ai::Unit::JaguarWarrior: os << "JaguarWarrior"; break;
    case ai::Unit::Janissary: os << "Janissary"; break;
    case ai::Unit::Longbowman: os << "Longbowman"; break;
    case ai::Unit::Mameluke: os << "Mameluke"; break;
    case ai::Unit::Mangudai: os << "Mangudai"; break;
    case ai::Unit::Petard: os << "Petard"; break;
    case ai::Unit::PlumedArcher: os << "PlumedArcher"; break;
    case ai::Unit::Samurai: os << "Samurai"; break;
    case ai::Unit::Tarkan: os << "Tarkan"; break;
    case ai::Unit::TeutonicKnight: os << "TeutonicKnight"; break;
    case ai::Unit::ThrowingAxeman: os << "ThrowingAxeman"; break;
    case ai::Unit::Trebuchet: os << "Trebuchet"; break;
    case ai::Unit::WarElephant: os << "WarElephant"; break;
    case ai::Unit::WarWagon: os << "WarWagon"; break;
    case ai::Unit::WoadRaider: os << "WoadRaider"; break;
    case ai::Unit::CannonGalleon: os << "CannonGalleon"; break;
    case ai::Unit::DemolitionShip: os << "DemolitionShip"; break;
    case ai::Unit::EliteCannonGalleon: os << "EliteCannonGalleon"; break;
    case ai::Unit::EliteLongboat: os << "EliteLongboat"; break;
    case ai::Unit::EliteTurtleShip: os << "EliteTurtleShip"; break;
    case ai::Unit::FastFireShip: os << "FastFireShip"; break;
    case ai::Unit::FireShip: os << "FireShip"; break;
    case ai::Unit::FishingShip: os << "FishingShip"; break;
    case ai::Unit::Galleon: os << "Galleon"; break;
    case ai::Unit::Galley: os << "Galley"; break;
    case ai::Unit::HeavyDemolitionShip: os << "HeavyDemolitionShip"; break;
    case ai::Unit::Longboat: os << "Longboat"; break;
    case ai::Unit::TradeCog: os << "TradeCog"; break;
    case ai::Unit::TransportShip: os << "TransportShip"; break;
    case ai::Unit::TurtleShip: os << "TurtleShip"; break;
    case ai::Unit::WarGalley: os << "WarGalley"; break;
    case ai::Unit::TradeCart: os << "TradeCart"; break;
    case ai::Unit::Missionary: os << "Missionary"; break;
    case ai::Unit::Monk: os << "Monk"; break;
    case ai::Unit::BatteringRam: os << "BatteringRam"; break;
    case ai::Unit::BombardCannon: os << "BombardCannon"; break;
    case ai::Unit::CappedRam: os << "CappedRam"; break;
    case ai::Unit::HeavyScorpion: os << "HeavyScorpion"; break;
    case ai::Unit::Mangonel: os << "Mangonel"; break;
    case ai::Unit::Onager: os << "Onager"; break;
    case ai::Unit::Scorpion: os << "Scorpion"; break;
    case ai::Unit::SiegeOnager: os << "SiegeOnager"; break;
    case ai::Unit::SiegeRam: os << "SiegeRam"; break;
    case ai::Unit::Camel: os << "Camel"; break;
    case ai::Unit::Cavalier: os << "Cavalier"; break;
    case ai::Unit::HeavyCamel: os << "HeavyCamel"; break;
    case ai::Unit::Hussar: os << "Hussar"; break;
    case ai::Unit::Knight: os << "Knight"; break;
    case ai::Unit::LightCavalry: os << "LightCavalry"; break;
    case ai::Unit::Paladin: os << "Paladin"; break;
    case ai::Unit::ScoutCavalry: os << "ScoutCavalry"; break;
    case ai::Unit::Villager: os << "Villager"; break;
    case ai::Unit::ArcherLine: os << "ArcherLine"; break;
    case ai::Unit::CavalryArcherLine: os << "CavalryArcherLine"; break;
    case ai::Unit::SkirmisherLine: os << "SkirmisherLine"; break;
    case ai::Unit::EagleWarriorLine: os << "EagleWarriorLine"; break;
    case ai::Unit::MilitiamanLine: os << "MilitiamanLine"; break;
    case ai::Unit::SpearmanLine: os << "SpearmanLine"; break;
    case ai::Unit::BerserkLine: os << "BerserkLine"; break;
    case ai::Unit::CataphractLine: os << "CataphractLine"; break;
    case ai::Unit::ChuKoNuLine: os << "ChuKoNuLine"; break;
    case ai::Unit::ConquistadorLine: os << "ConquistadorLine"; break;
    case ai::Unit::HuskarlLine: os << "HuskarlLine"; break;
    case ai::Unit::JaguarWarriorLine: os << "JaguarWarriorLine"; break;
    case ai::Unit::JanissaryLine: os << "JanissaryLine"; break;
    case ai::Unit::LongbowmanLine: os << "LongbowmanLine"; break;
    case ai::Unit::MamelukeLine: os << "MamelukeLine"; break;
    case ai::Unit::MangudaiLine: os << "MangudaiLine"; break;
    case ai::Unit::PlumedArcherLine: os << "PlumedArcherLine"; break;
    case ai::Unit::SamuraiLine: os << "SamuraiLine"; break;
    case ai::Unit::TarkanLine: os << "TarkanLine"; break;
    case ai::Unit::TeutonicKnightLine: os << "TeutonicKnightLine"; break;
    case ai::Unit::ThrowingAxemanLine: os << "ThrowingAxemanLine"; break;
    case ai::Unit::WarElephantLine: os << "WarElephantLine"; break;
    case ai::Unit::WarWagonLine: os << "WarWagonLine"; break;
    case ai::Unit::WoadRaiderLine: os << "WoadRaiderLine"; break;
    case ai::Unit::CannonGalleonLine: os << "CannonGalleonLine"; break;
    case ai::Unit::DemolitionShipLine: os << "DemolitionShipLine"; break;
    case ai::Unit::FireShipLine: os << "FireShipLine"; break;
    case ai::Unit::GalleyLine: os << "GalleyLine"; break;
    case ai::Unit::LongboatLine: os << "LongboatLine"; break;
    case ai::Unit::TurtleShipLine: os << "TurtleShipLine"; break;
    case ai::Unit::BatteringRamLine: os << "BatteringRamLine"; break;
    case ai::Unit::MangonelLine: os << "MangonelLine"; break;
    case ai::Unit::ScorpionLine: os << "ScorpionLine"; break;
    case ai::Unit::CamelLine: os << "CamelLine"; break;
    case ai::Unit::KnightLine: os << "KnightLine"; break;
    case ai::Unit::ScoutCavalryLine: os << "ScoutCavalryLine"; break;
    case ai::Unit::MyEliteUniqueUnit: os << "MyEliteUniqueUnit"; break;
    case ai::Unit::MyUniqueUnit: os << "MyUniqueUnit"; break;
    case ai::Unit::MyUniqueUnitLine: os << "MyUniqueUnitLine"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::PlayerNumberType type)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::PlayerNumberType::";

    //:%s- \+\(.*\),.*-case ai::PlayerNumberType::\1: os << "\1"; break;-
    switch(type) {
    case ai::PlayerNumberType::AnyAlly: os << "AnyAlly"; break;
    case ai::PlayerNumberType::AnyComputer: os << "AnyComputer"; break;
    case ai::PlayerNumberType::AnyComputerAlly: os << "AnyComputerAlly"; break;
    case ai::PlayerNumberType::AnyComputerEnemy: os << "AnyComputerEnemy"; break;
    case ai::PlayerNumberType::AnyComputerNeutral: os << "AnyComputerNeutral"; break;
    case ai::PlayerNumberType::AnyEnemy: os << "AnyEnemy"; break;
    case ai::PlayerNumberType::AnyHuman: os << "AnyHuman"; break;
    case ai::PlayerNumberType::AnyHumanAlly: os << "AnyHumanAlly"; break;
    case ai::PlayerNumberType::AnyHumanEnemy: os << "AnyHumanEnemy"; break;
    case ai::PlayerNumberType::AnyHumanNeutral: os << "AnyHumanNeutral"; break;
    case ai::PlayerNumberType::AnyNeutral: os << "AnyNeutral"; break;
    case ai::PlayerNumberType::EveryAlly: os << "EveryAlly"; break;
    case ai::PlayerNumberType::EveryComputer: os << "EveryComputer"; break;
    case ai::PlayerNumberType::EveryEnemy: os << "EveryEnemy"; break;
    case ai::PlayerNumberType::EveryHuman: os << "EveryHuman"; break;
    case ai::PlayerNumberType::EveryNeutral: os << "EveryNeutral"; break;
    case ai::PlayerNumberType::MyPlayerNumber: os << "MyPlayerNumber"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::StrategicNumberName name)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::StrategicNumberName::";

    //:%s- \+\(.*\),.*-case ai::StrategicNumberName::\1: os << "\1"; break;-
    switch(name) {
    case ai::StrategicNumberName::SnPercentCivilianExplorers: os << "SnPercentCivilianExplorers"; break;
    case ai::StrategicNumberName::SnPercentCivilianBuilders: os << "SnPercentCivilianBuilders"; break;
    case ai::StrategicNumberName::SnPercentCivilianGatherers: os << "SnPercentCivilianGatherers"; break;
    case ai::StrategicNumberName::SnCapCivilianExplorers: os << "SnCapCivilianExplorers"; break;
    case ai::StrategicNumberName::SnCapCivilianBuilders: os << "SnCapCivilianBuilders"; break;
    case ai::StrategicNumberName::SnCapCivilianGatherers: os << "SnCapCivilianGatherers"; break;
    case ai::StrategicNumberName::SnMinimumAttackGroupSize: os << "SnMinimumAttackGroupSize"; break;
    case ai::StrategicNumberName::SnTotalNumberExplorers: os << "SnTotalNumberExplorers"; break;
    case ai::StrategicNumberName::SnPercentEnemySightedResponse: os << "SnPercentEnemySightedResponse"; break;
    case ai::StrategicNumberName::SnEnemySightedResponseDistance: os << "SnEnemySightedResponseDistance"; break;
    case ai::StrategicNumberName::SnSentryDistance: os << "SnSentryDistance"; break;
    case ai::StrategicNumberName::SnRelicReturnDistance: os << "SnRelicReturnDistance"; break;
    case ai::StrategicNumberName::SnMinimumDefendGroupSize: os << "SnMinimumDefendGroupSize"; break;
    case ai::StrategicNumberName::SnMaximumAttackGroupSize: os << "SnMaximumAttackGroupSize"; break;
    case ai::StrategicNumberName::SnMaximumDefendGroupSize: os << "SnMaximumDefendGroupSize"; break;
    case ai::StrategicNumberName::SnMinimumPeaceLikeLevel: os << "SnMinimumPeaceLikeLevel"; break;
    case ai::StrategicNumberName::SnPercentExplorationRequired: os << "SnPercentExplorationRequired"; break;
    case ai::StrategicNumberName::SnZeroPriorityDistance: os << "SnZeroPriorityDistance"; break;
    case ai::StrategicNumberName::SnMinimumCivilianExplorers: os << "SnMinimumCivilianExplorers"; break;
    case ai::StrategicNumberName::SnNumberAttackGroups: os << "SnNumberAttackGroups"; break;
    case ai::StrategicNumberName::SnNumberDefendGroups: os << "SnNumberDefendGroups"; break;
    case ai::StrategicNumberName::SnAttackGroupGatherSpacing: os << "SnAttackGroupGatherSpacing"; break;
    case ai::StrategicNumberName::SnNumberExploreGroups: os << "SnNumberExploreGroups"; break;
    case ai::StrategicNumberName::SnMinimumExploreGroupSize: os << "SnMinimumExploreGroupSize"; break;
    case ai::StrategicNumberName::SnMaximumExploreGroupSize: os << "SnMaximumExploreGroupSize"; break;
    case ai::StrategicNumberName::SnGoldDefendPriority: os << "SnGoldDefendPriority"; break;
    case ai::StrategicNumberName::SnStoneDefendPriority: os << "SnStoneDefendPriority"; break;
    case ai::StrategicNumberName::SnForageDefendPriority: os << "SnForageDefendPriority"; break;
    case ai::StrategicNumberName::SnRelicDefendPriority: os << "SnRelicDefendPriority"; break;
    case ai::StrategicNumberName::SnTownDefendPriority: os << "SnTownDefendPriority"; break;
    case ai::StrategicNumberName::SnDefenseDistance: os << "SnDefenseDistance"; break;
    case ai::StrategicNumberName::SnNumberBoatAttackGroups: os << "SnNumberBoatAttackGroups"; break;
    case ai::StrategicNumberName::SnMinimumBoatAttackGroupSize: os << "SnMinimumBoatAttackGroupSize"; break;
    case ai::StrategicNumberName::SnMaximumBoatAttackGroupSize: os << "SnMaximumBoatAttackGroupSize"; break;
    case ai::StrategicNumberName::SnNumberBoatExploreGroups: os << "SnNumberBoatExploreGroups"; break;
    case ai::StrategicNumberName::SnMinimumBoatExploreGroupSize: os << "SnMinimumBoatExploreGroupSize"; break;
    case ai::StrategicNumberName::SnMaximumBoatExploreGroupSize: os << "SnMaximumBoatExploreGroupSize"; break;
    case ai::StrategicNumberName::SnNumberBoatDefendGroups: os << "SnNumberBoatDefendGroups"; break;
    case ai::StrategicNumberName::SnMinimumBoatDefendGroupSize: os << "SnMinimumBoatDefendGroupSize"; break;
    case ai::StrategicNumberName::SnMaximumBoatDefendGroupSize: os << "SnMaximumBoatDefendGroupSize"; break;
    case ai::StrategicNumberName::SnDockDefendPriority: os << "SnDockDefendPriority"; break;
    case ai::StrategicNumberName::SnSentryDistanceVariation: os << "SnSentryDistanceVariation"; break;
    case ai::StrategicNumberName::SnMinimumTownSize: os << "SnMinimumTownSize"; break;
    case ai::StrategicNumberName::SnMaximumTownSize: os << "SnMaximumTownSize"; break;
    case ai::StrategicNumberName::SnGroupCommanderSelectionMethod: os << "SnGroupCommanderSelectionMethod"; break;
    case ai::StrategicNumberName::SnConsecutiveIdleUnitLimit: os << "SnConsecutiveIdleUnitLimit"; break;
    case ai::StrategicNumberName::SnTargetEvaluationDistance: os << "SnTargetEvaluationDistance"; break;
    case ai::StrategicNumberName::SnTargetEvaluationHitpoints: os << "SnTargetEvaluationHitpoints"; break;
    case ai::StrategicNumberName::SnTargetEvaluationDamageCapability: os << "SnTargetEvaluationDamageCapability"; break;
    case ai::StrategicNumberName::SnTargetEvaluationKills: os << "SnTargetEvaluationKills"; break;
    case ai::StrategicNumberName::SnTargetEvaluationAllyProximity: os << "SnTargetEvaluationAllyProximity"; break;
    case ai::StrategicNumberName::SnTargetEvaluationRof: os << "SnTargetEvaluationRof"; break;
    case ai::StrategicNumberName::SnTargetEvaluationRandomness: os << "SnTargetEvaluationRandomness"; break;
    case ai::StrategicNumberName::SnCampMaxDistance: os << "SnCampMaxDistance"; break;
    case ai::StrategicNumberName::SnMillMaxDistance: os << "SnMillMaxDistance"; break;
    case ai::StrategicNumberName::SnTargetEvaluationAttackAttempts: os << "SnTargetEvaluationAttackAttempts"; break;
    case ai::StrategicNumberName::SnTargetEvaluationRange: os << "SnTargetEvaluationRange"; break;
    case ai::StrategicNumberName::SnDefendOverlapDistance: os << "SnDefendOverlapDistance"; break;
    case ai::StrategicNumberName::SnScaleMinimumAttackGroupSize: os << "SnScaleMinimumAttackGroupSize"; break;
    case ai::StrategicNumberName::SnScaleMaximumAttackGroupSize: os << "SnScaleMaximumAttackGroupSize"; break;
    case ai::StrategicNumberName::SnAttackGroupSizeRandomness: os << "SnAttackGroupSizeRandomness"; break;
    case ai::StrategicNumberName::SnScalingFrequency: os << "SnScalingFrequency"; break;
    case ai::StrategicNumberName::SnMaximumGaiaAttackResponse: os << "SnMaximumGaiaAttackResponse"; break;
    case ai::StrategicNumberName::SnBuildFrequency: os << "SnBuildFrequency"; break;
    case ai::StrategicNumberName::SnAttackSeparationTimeRandomness: os << "SnAttackSeparationTimeRandomness"; break;
    case ai::StrategicNumberName::SnAttackIntelligence: os << "SnAttackIntelligence"; break;
    case ai::StrategicNumberName::SnInitialAttackDelay: os << "SnInitialAttackDelay"; break;
    case ai::StrategicNumberName::SnSaveScenarioInformation: os << "SnSaveScenarioInformation"; break;
    case ai::StrategicNumberName::SnSpecialAttackType1: os << "SnSpecialAttackType1"; break;
    case ai::StrategicNumberName::SnSpecialAttackInfluence1: os << "SnSpecialAttackInfluence1"; break;
    case ai::StrategicNumberName::SnMinimumWaterBodySizeForDock: os << "SnMinimumWaterBodySizeForDock"; break;
    case ai::StrategicNumberName::SnNumberBuildAttemptsBeforeSkip: os << "SnNumberBuildAttemptsBeforeSkip"; break;
    case ai::StrategicNumberName::SnMaxSkipsPerAttempt: os << "SnMaxSkipsPerAttempt"; break;
    case ai::StrategicNumberName::SnFoodGathererPercentage: os << "SnFoodGathererPercentage"; break;
    case ai::StrategicNumberName::SnGoldGathererPercentage: os << "SnGoldGathererPercentage"; break;
    case ai::StrategicNumberName::SnStoneGathererPercentage: os << "SnStoneGathererPercentage"; break;
    case ai::StrategicNumberName::SnWoodGathererPercentage: os << "SnWoodGathererPercentage"; break;
    case ai::StrategicNumberName::SnTargetEvaluationContinent: os << "SnTargetEvaluationContinent"; break;
    case ai::StrategicNumberName::SnTargetEvaluationSiegeWeapon: os << "SnTargetEvaluationSiegeWeapon"; break;
    case ai::StrategicNumberName::SnGroupLeaderDefenseDistance: os << "SnGroupLeaderDefenseDistance"; break;
    case ai::StrategicNumberName::SnInitialAttackDelayType: os << "SnInitialAttackDelayType"; break;
    case ai::StrategicNumberName::SnBlotExplorationMap: os << "SnBlotExplorationMap"; break;
    case ai::StrategicNumberName::SnBlotSize: os << "SnBlotSize"; break;
    case ai::StrategicNumberName::SnIntelligentGathering: os << "SnIntelligentGathering"; break;
    case ai::StrategicNumberName::SnTaskUngroupedSoldiers: os << "SnTaskUngroupedSoldiers"; break;
    case ai::StrategicNumberName::SnTargetEvaluationBoat: os << "SnTargetEvaluationBoat"; break;
    case ai::StrategicNumberName::SnNumberEnemyObjectsRequired: os << "SnNumberEnemyObjectsRequired"; break;
    case ai::StrategicNumberName::SnNumberMaxSkipCycles: os << "SnNumberMaxSkipCycles"; break;
    case ai::StrategicNumberName::SnRetaskGatherAmount: os << "SnRetaskGatherAmount"; break;
    case ai::StrategicNumberName::SnMaxRetaskGatherAmount: os << "SnMaxRetaskGatherAmount"; break;
    case ai::StrategicNumberName::SnMaxBuildPlanGathererPercentage: os << "SnMaxBuildPlanGathererPercentage"; break;
    case ai::StrategicNumberName::SnFoodDropsiteDistance: os << "SnFoodDropsiteDistance"; break;
    case ai::StrategicNumberName::SnWoodDropsiteDistance: os << "SnWoodDropsiteDistance"; break;
    case ai::StrategicNumberName::SnStoneDropsiteDistance: os << "SnStoneDropsiteDistance"; break;
    case ai::StrategicNumberName::SnGoldDropsiteDistance: os << "SnGoldDropsiteDistance"; break;
    case ai::StrategicNumberName::SnInitialExplorationRequired: os << "SnInitialExplorationRequired"; break;
    case ai::StrategicNumberName::SnRandomPlacementFactor: os << "SnRandomPlacementFactor"; break;
    case ai::StrategicNumberName::SnRequiredForestTiles: os << "SnRequiredForestTiles"; break;
    case ai::StrategicNumberName::SnAttackDiplomacyImpact: os << "SnAttackDiplomacyImpact"; break;
    case ai::StrategicNumberName::SnPercentHalfExploration: os << "SnPercentHalfExploration"; break;
    case ai::StrategicNumberName::SnTargetEvaluationTimeKillRatio: os << "SnTargetEvaluationTimeKillRatio"; break;
    case ai::StrategicNumberName::SnTargetEvaluationInProgress: os << "SnTargetEvaluationInProgress"; break;
    case ai::StrategicNumberName::SnAttackWinningPlayer: os << "SnAttackWinningPlayer"; break;
    case ai::StrategicNumberName::SnCoopShareInformation: os << "SnCoopShareInformation"; break;
    case ai::StrategicNumberName::SnAttackWinningPlayerFactor: os << "SnAttackWinningPlayerFactor"; break;
    case ai::StrategicNumberName::SnCoopShareAttacking: os << "SnCoopShareAttacking"; break;
    case ai::StrategicNumberName::SnCoopShareAttackingInterval: os << "SnCoopShareAttackingInterval"; break;
    case ai::StrategicNumberName::SnPercentageExploreExterminators: os << "SnPercentageExploreExterminators"; break;
    case ai::StrategicNumberName::SnTrackPlayerHistory: os << "SnTrackPlayerHistory"; break;
    case ai::StrategicNumberName::SnMinimumDropsiteBuffer: os << "SnMinimumDropsiteBuffer"; break;
    case ai::StrategicNumberName::SnUseByTypeMaxGathering: os << "SnUseByTypeMaxGathering"; break;
    case ai::StrategicNumberName::SnMinimumBoarHuntGroupSize: os << "SnMinimumBoarHuntGroupSize"; break;
    case ai::StrategicNumberName::SnMinimumAmountForTrading: os << "SnMinimumAmountForTrading"; break;
    case ai::StrategicNumberName::SnEasiestReactionPercentage: os << "SnEasiestReactionPercentage"; break;
    case ai::StrategicNumberName::SnEasierReactionPercentage: os << "SnEasierReactionPercentage"; break;
    case ai::StrategicNumberName::SnHitsBeforeAllianceChange: os << "SnHitsBeforeAllianceChange"; break;
    case ai::StrategicNumberName::SnAllowCivilianDefense: os << "SnAllowCivilianDefense"; break;
    case ai::StrategicNumberName::SnNumberForwardBuilders: os << "SnNumberForwardBuilders"; break;
    case ai::StrategicNumberName::SnPercentAttackSoldiers: os << "SnPercentAttackSoldiers"; break;
    case ai::StrategicNumberName::SnPercentAttackBoats: os << "SnPercentAttackBoats"; break;
    case ai::StrategicNumberName::SnDoNotScaleForDifficultyLevel: os << "SnDoNotScaleForDifficultyLevel"; break;
    case ai::StrategicNumberName::SnGroupFormDistance: os << "SnGroupFormDistance"; break;
    case ai::StrategicNumberName::SnIgnoreAttackGroupUnderAttack: os << "SnIgnoreAttackGroupUnderAttack"; break;
    case ai::StrategicNumberName::SnGatherDefenseUnits: os << "SnGatherDefenseUnits"; break;
    case ai::StrategicNumberName::SnMaximumWoodDropDistance: os << "SnMaximumWoodDropDistance"; break;
    case ai::StrategicNumberName::SnMaximumFoodDropDistance: os << "SnMaximumFoodDropDistance"; break;
    case ai::StrategicNumberName::SnMaximumHuntDropDistance: os << "SnMaximumHuntDropDistance"; break;
    case ai::StrategicNumberName::SnMaximumFishBoatDropDistance: os << "SnMaximumFishBoatDropDistance"; break;
    case ai::StrategicNumberName::SnMaximumGoldDropDistance: os << "SnMaximumGoldDropDistance"; break;
    case ai::StrategicNumberName::SnMaximumStoneDropDistance: os << "SnMaximumStoneDropDistance"; break;
    case ai::StrategicNumberName::SnGatherIdleSoldiersAtCenter: os << "SnGatherIdleSoldiersAtCenter"; break;
    case ai::StrategicNumberName::SnGarrisonRams: os << "SnGarrisonRams"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ai::Fact fact)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "ai::Fact::";

    //:%s- \+\(.*\),.*-case ai::Fact::\1: os << "\1"; break;-
    switch(fact) {
    case ai::Fact::Trueval: os << "Trueval"; break;
    case ai::Fact::Falseval: os << "Falseval"; break;
    case ai::Fact::AttackSoldierCount: os << "AttackSoldierCount"; break;
    case ai::Fact::AttackWarboatCount: os << "AttackWarboatCount"; break;
    case ai::Fact::BuildingAvailable: os << "BuildingAvailable"; break;
    case ai::Fact::BuildingCount: os << "BuildingCount"; break;
    case ai::Fact::BuildingCountTotal: os << "BuildingCountTotal"; break;
    case ai::Fact::BuildingTypeCount: os << "BuildingTypeCount"; break;
    case ai::Fact::BuildingTypeCountTotal: os << "BuildingTypeCountTotal"; break;
    case ai::Fact::CanAffordBuilding: os << "CanAffordBuilding"; break;
    case ai::Fact::CanAffordCompleteWall: os << "CanAffordCompleteWall"; break;
    case ai::Fact::CanAffordResearch: os << "CanAffordResearch"; break;
    case ai::Fact::CanAffordUnit: os << "CanAffordUnit"; break;
    case ai::Fact::CanBuild: os << "CanBuild"; break;
    case ai::Fact::CanBuildGate: os << "CanBuildGate"; break;
    case ai::Fact::CanBuildGateWithEscrow: os << "CanBuildGateWithEscrow"; break;
    case ai::Fact::CanBuildWall: os << "CanBuildWall"; break;
    case ai::Fact::CanBuildWallWithEscrow: os << "CanBuildWallWithEscrow"; break;
    case ai::Fact::CanBuildWithEscrow: os << "CanBuildWithEscrow"; break;
    case ai::Fact::CanBuyCommodity: os << "CanBuyCommodity"; break;
    case ai::Fact::CanResearch: os << "CanResearch"; break;
    case ai::Fact::CanResearchWithEscrow: os << "CanResearchWithEscrow"; break;
    case ai::Fact::CanSellCommodity: os << "CanSellCommodity"; break;
    case ai::Fact::CanSpy: os << "CanSpy"; break;
    case ai::Fact::CanSpyWithEscrow: os << "CanSpyWithEscrow"; break;
    case ai::Fact::CanTrain: os << "CanTrain"; break;
    case ai::Fact::CanTrainWithEscrow: os << "CanTrainWithEscrow"; break;
    case ai::Fact::CcPlayersBuildingCount: os << "CcPlayersBuildingCount"; break;
    case ai::Fact::CcPlayersBuildingTypeCount: os << "CcPlayersBuildingTypeCount"; break;
    case ai::Fact::CcPlayersUnitCount: os << "CcPlayersUnitCount"; break;
    case ai::Fact::CcPlayersUnitTypeCount: os << "CcPlayersUnitTypeCount"; break;
    case ai::Fact::CheatsEnabled: os << "CheatsEnabled"; break;
    case ai::Fact::CivSelected: os << "CivSelected"; break;
    case ai::Fact::CivilianPopulation: os << "CivilianPopulation"; break;
    case ai::Fact::CommodityBuyingPrice: os << "CommodityBuyingPrice"; break;
    case ai::Fact::CommoditySellingPrice: os << "CommoditySellingPrice"; break;
    case ai::Fact::CurrentAge: os << "CurrentAge"; break;
    case ai::Fact::CurrentAgeTime: os << "CurrentAgeTime"; break;
    case ai::Fact::CurrentScore: os << "CurrentScore"; break;
    case ai::Fact::DeathMatchGame: os << "DeathMatchGame"; break;
    case ai::Fact::DefendSoldierCount: os << "DefendSoldierCount"; break;
    case ai::Fact::DefendWarboatCount: os << "DefendWarboatCount"; break;
    case ai::Fact::Difficulty: os << "Difficulty"; break;
    case ai::Fact::Doctrine: os << "Doctrine"; break;
    case ai::Fact::DropsiteMinDistance: os << "DropsiteMinDistance"; break;
    case ai::Fact::EnemyBuildingsInTown: os << "EnemyBuildingsInTown"; break;
    case ai::Fact::EnemyCapturedRelics: os << "EnemyCapturedRelics"; break;
    case ai::Fact::EscrowAmount: os << "EscrowAmount"; break;
    case ai::Fact::EventDetected: os << "EventDetected"; break;
    case ai::Fact::FoodAmount: os << "FoodAmount"; break;
    case ai::Fact::GameTime: os << "GameTime"; break;
    case ai::Fact::Goal: os << "Goal"; break;
    case ai::Fact::GoldAmount: os << "GoldAmount"; break;
    case ai::Fact::HousingHeadroom: os << "HousingHeadroom"; break;
    case ai::Fact::IdleFarmCount: os << "IdleFarmCount"; break;
    case ai::Fact::MapSize: os << "MapSize"; break;
    case ai::Fact::MapType: os << "MapType"; break;
    case ai::Fact::MilitaryPopulation: os << "MilitaryPopulation"; break;
    case ai::Fact::PlayerComputer: os << "PlayerComputer"; break;
    case ai::Fact::PlayerHuman: os << "PlayerHuman"; break;
    case ai::Fact::PlayerInGame: os << "PlayerInGame"; break;
    case ai::Fact::PlayerNumber: os << "PlayerNumber"; break;
    case ai::Fact::PlayerResigned: os << "PlayerResigned"; break;
    case ai::Fact::PlayerValid: os << "PlayerValid"; break;
    case ai::Fact::PlayersBuildingCount: os << "PlayersBuildingCount"; break;
    case ai::Fact::PlayersBuildingTypeCount: os << "PlayersBuildingTypeCount"; break;
    case ai::Fact::PlayersCiv: os << "PlayersCiv"; break;
    case ai::Fact::PlayersCivilianPopulation: os << "PlayersCivilianPopulation"; break;
    case ai::Fact::PlayersCurrentAge: os << "PlayersCurrentAge"; break;
    case ai::Fact::PlayersCurrentAgeTime: os << "PlayersCurrentAgeTime"; break;
    case ai::Fact::PlayersMilitaryPopulation: os << "PlayersMilitaryPopulation"; break;
    case ai::Fact::PlayersPopulation: os << "PlayersPopulation"; break;
    case ai::Fact::PlayersScore: os << "PlayersScore"; break;
    case ai::Fact::PlayersStance: os << "PlayersStance"; break;
    case ai::Fact::PlayersTribute: os << "PlayersTribute"; break;
    case ai::Fact::PlayersTributeMemory: os << "PlayersTributeMemory"; break;
    case ai::Fact::PlayersUnitCount: os << "PlayersUnitCount"; break;
    case ai::Fact::PlayersUnitTypeCount: os << "PlayersUnitTypeCount"; break;
    case ai::Fact::Population: os << "Population"; break;
    case ai::Fact::PopulationCap: os << "PopulationCap"; break;
    case ai::Fact::PopulationHeadroom: os << "PopulationHeadroom"; break;
    case ai::Fact::RandomNumber: os << "RandomNumber"; break;
    case ai::Fact::RegicideGame: os << "RegicideGame"; break;
    case ai::Fact::ResearchAvailable: os << "ResearchAvailable"; break;
    case ai::Fact::ResearchCompleted: os << "ResearchCompleted"; break;
    case ai::Fact::ResourceFound: os << "ResourceFound"; break;
    case ai::Fact::SharedGoal: os << "SharedGoal"; break;
    case ai::Fact::SheepAndForageTooFar: os << "SheepAndForageTooFar"; break;
    case ai::Fact::SoldierCount: os << "SoldierCount"; break;
    case ai::Fact::StanceToward: os << "StanceToward"; break;
    case ai::Fact::StartingAge: os << "StartingAge"; break;
    case ai::Fact::StartingResources: os << "StartingResources"; break;
    case ai::Fact::StoneAmount: os << "StoneAmount"; break;
    case ai::Fact::StrategicNumber: os << "StrategicNumber"; break;
    case ai::Fact::TauntDetected: os << "TauntDetected"; break;
    case ai::Fact::TimerTriggered: os << "TimerTriggered"; break;
    case ai::Fact::TownUnderAttack: os << "TownUnderAttack"; break;
    case ai::Fact::UnitAvailable: os << "UnitAvailable"; break;
    case ai::Fact::UnitCount: os << "UnitCount"; break;
    case ai::Fact::UnitCountTotal: os << "UnitCountTotal"; break;
    case ai::Fact::UnitTypeCount: os << "UnitTypeCount"; break;
    case ai::Fact::UnitTypeCountTotal: os << "UnitTypeCountTotal"; break;
    case ai::Fact::VictoryCondition: os << "VictoryCondition"; break;
    case ai::Fact::WallCompletedPercentage: os << "WallCompletedPercentage"; break;
    case ai::Fact::WallInvisiblePercentage: os << "WallInvisiblePercentage"; break;
    case ai::Fact::WarboatCount: os << "WarboatCount"; break;
    case ai::Fact::WoodAmount: os << "WoodAmount"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}
