#pragma once
#include "gen/enums.h"

#include "core/Logger.h"

#include <unordered_set>

namespace ai
{
    int researchId(const ResearchItem item)
    {
        switch(item) {
            case ResearchItem::RiArbalest: return 237;
            case ResearchItem::RiCrossbow: return 100;
            case ResearchItem::RiEliteSkirmisher: return 98;
            case ResearchItem::RiHandCannon: return 85;
            case ResearchItem::RiHeavyCavalryArcher: return 218;
            case ResearchItem::RiParthianTactics: return 436;
            case ResearchItem::RiThumbRing: return 437;
            case ResearchItem::RiChampion: return 264;
            case ResearchItem::RiEliteEagleWarrior: return 434;
            case ResearchItem::RiHalberdier: return 429;
            case ResearchItem::RiLongSwordsman: return 207;
            case ResearchItem::RiManAtArms: return 222;
            case ResearchItem::RiPikeman: return 197;
            case ResearchItem::RiSquires: return 215;
            case ResearchItem::RiTracking: return 90;
            case ResearchItem::RiTwoHandedSwordsman: return 217;
            case ResearchItem::RiBlastFurnace: return 75;
            case ResearchItem::RiBodkinArrow: return 200;
            case ResearchItem::RiBracer: return 201;
            case ResearchItem::RiChainBarding: return 82;
            case ResearchItem::RiChainMail: return 76;
            case ResearchItem::RiFletching: return 199;
            case ResearchItem::RiForging: return 67;
            case ResearchItem::RiIronCasting: return 68;
            case ResearchItem::RiLeatherArcherArmor: return 212;
            case ResearchItem::RiPaddedArcherArmor: return 211;
            case ResearchItem::RiPlateBarding: return 80;
            case ResearchItem::RiPlateMail: return 77;
            case ResearchItem::RiRingArcherArmor: return 219;
            case ResearchItem::RiScaleBarding: return 81;
            case ResearchItem::RiScaleMail: return 74;
            case ResearchItem::RiConscription: return 315;
            case ResearchItem::RiHoardings: return 379;
            case ResearchItem::RiSappers: return 321;
            case ResearchItem::RiEliteBerserk: return 398;
            case ResearchItem::RiEliteCataphract: return 361;
            case ResearchItem::RiEliteChuKoNu: return 362;
            case ResearchItem::RiEliteHuskarl: return 365;
            case ResearchItem::RiEliteJanissary: return 369;
            case ResearchItem::RiEliteLongbowman: return 360;
            case ResearchItem::RiEliteMameluke: return 368;
            case ResearchItem::RiEliteMangudai: return 371;
            case ResearchItem::RiEliteSamurai: return 366;
            case ResearchItem::RiEliteTeutonicKnight: return 364;
            case ResearchItem::RiEliteThrowingAxeman: return 363;
            case ResearchItem::RiEliteWarElephant: return 367;
            case ResearchItem::RiEliteWoadRaider: return 370;
            case ResearchItem::RiCannonGalleon: return 37;
            case ResearchItem::RiCareening: return 374;
            case ResearchItem::RiDeckGuns: return 376;
            case ResearchItem::RiDryDock: return 375;
            case ResearchItem::RiFastFireShip: return 246;
            case ResearchItem::RiGalleon: return 35;
            case ResearchItem::RiHeavyDemolitionShip: return 244;
            case ResearchItem::RiShipwright: return 373;
            case ResearchItem::RiWarGalley: return 34;
            case ResearchItem::RiEliteLongboat: return 372;
            case ResearchItem::RiBowSaw: return 203;
            case ResearchItem::RiDoubleBitAxe: return 202;
            case ResearchItem::RiTwoManSaw: return 221;
            case ResearchItem::RiBanking: return 17;
            case ResearchItem::RiCaravan: return 48;
            case ResearchItem::RiCartography: return 19;
            case ResearchItem::RiCoinage: return 23;
            case ResearchItem::RiGuilds: return 15;
            case ResearchItem::RiCropRotation: return 12;
            case ResearchItem::RiHeavyPlow: return 13;
            case ResearchItem::RiHorseCollar: return 14;
            case ResearchItem::RiGoldMining: return 55;
            case ResearchItem::RiGoldShaftMining: return 182;
            case ResearchItem::RiStoneMining: return 278;
            case ResearchItem::RiStoneShaftMining: return 279;
            case ResearchItem::RiAtonement: return 319;
            case ResearchItem::RiBlockPrinting: return 230;
            case ResearchItem::RiFaith: return 45;
            case ResearchItem::RiFervor: return 252;
            case ResearchItem::RiHeresy: return 439;
            case ResearchItem::RiIllumination: return 233;
            case ResearchItem::RiRedemption: return 316;
            case ResearchItem::RiSanctity: return 231;
            case ResearchItem::RiTheocracy: return 438;
            case ResearchItem::RiBombardCannon: return 188;
            case ResearchItem::RiHeavyScorpion: return 239;
            case ResearchItem::RiCappedRam: return 96;
            case ResearchItem::RiOnager: return 257;
            case ResearchItem::RiScorpion: return 94;
            case ResearchItem::RiSiegeOnager: return 320;
            case ResearchItem::RiSiegeRam: return 255;
            case ResearchItem::RiBloodlines: return 435;
            case ResearchItem::RiCavalier: return 209;
            case ResearchItem::RiHeavyCamel: return 236;
            case ResearchItem::RiHusbandry: return 39;
            case ResearchItem::RiHussar: return 428;
            case ResearchItem::RiLightCavalry: return 254;
            case ResearchItem::RiPaladin: return 265;
            case ResearchItem::RiHandCart: return 249;
            case ResearchItem::RiLoom: return 22;
            case ResearchItem::RiTownPatrol: return 280;
            case ResearchItem::RiTownWatch: return 8;
            case ResearchItem::RiWheelBarrow: return 213;
            case ResearchItem::RiArchitecture: return 51;
            case ResearchItem::RiBallistics: return 93;
            case ResearchItem::RiBombardTower: return 64;
            case ResearchItem::RiChemistry: return 47;
            case ResearchItem::RiFortifiedWall: return 194;
            case ResearchItem::RiGuardTower: return 140;
            case ResearchItem::RiHeatedShot: return 380;
            case ResearchItem::RiKeep: return 63;
            case ResearchItem::RiMasonry: return 50;
            case ResearchItem::RiMurderHoles: return 322;
            case ResearchItem::RiSiegeEngineers: return 377;
            case ResearchItem::RiStonecutting: return 54;
            default: return -1;
        }
    }

    enum class OtherUnits {
        Gate
    };

    int unitId(const OtherUnits &unit)
    {
        switch (unit) {
        case OtherUnits::Gate: return 487;
        default: return -1;
        }
    }

    int unitId(const WallType &wall)
    {
        switch (wall) {
        case WallType::FortifiedWall: return 155;
        case WallType::PalisadeWall: return 72;
        case WallType::StoneWall: return 117;
        default: return -1;
        }
    }

    int unitId(const Building &building)
    {
        switch (building) {
        case Building::ArcheryRange: return 87;
        case Building::Barracks: return 12;
        case Building::Blacksmith: return 103;
        case Building::BombardTower: return 236;
        case Building::Castle: return 82;
        case Building::Monastery: return 104;
        case Building::Dock: return 45;
        case Building::Farm: return 50;
        case Building::FishTrap: return 199;
        case Building::GuardTower: return 234;
        case Building::House: return 70;
        case Building::Keep: return 235;
        case Building::LumberCamp: return 562;
        case Building::Market: return 84;
        case Building::Mill: return 68;
        case Building::MiningCamp: return 584;
        case Building::Outpost: return 598;
        case Building::SiegeWorkshop: return 49;
        case Building::Stable: return 101;
        case Building::TownCenter: return 109;
        case Building::University: return 209;
        case Building::WatchTower: return 79;
        case Building::Wonder: return 276;
        default: return -1;
        }
    }

    int unitId(const Unit &unit)
    {
        switch (unit) {
        case Unit::Arbalest: return 492;
        case Unit::Archer: return 4;
        case Unit::CavalryArcher: return 39;
        case Unit::Crossbowman: return 24;
        case Unit::EliteSkirmisher: return 6;
        case Unit::HandCannoneer: return 5;
        case Unit::HeavyCavalryArcher: return 474;
        case Unit::Skirmisher: return 7;
        case Unit::EagleWarrior: return 751;
        case Unit::EliteEagleWarrior: return 752;
        case Unit::Champion: return 567;
        case Unit::Halberdier: return 359;
        case Unit::LongSwordsman: return 77;
        case Unit::ManAtArms: return 75;
        case Unit::Militiaman: return 74;
        case Unit::Petard: return 440;
        case Unit::Pikeman: return 358;
        case Unit::Spearman: return 93;
        case Unit::TwoHandedSwordsman: return 473;
        case Unit::Berserk: return 692;
        case Unit::Cataphract: return 40;
        case Unit::ChuKoNu: return 73;
        case Unit::Conquistador: return 771;
        case Unit::EliteBerserk: return 694;
        case Unit::EliteCataphract: return 553;
        case Unit::EliteChuKoNu: return 559;
        case Unit::EliteConquistador: return 773;
        case Unit::EliteHuskarl: return 555;
        case Unit::EliteJanissary: return 557;
        case Unit::EliteLongbowman: return 530;
        case Unit::EliteMameluke: return 556;
        case Unit::EliteMangudai: return 561;
        case Unit::ElitePlumedArcher: return 765;
        case Unit::EliteSamurai: return 560;
        case Unit::EliteTarkan: return 757;
        case Unit::EliteTeutonicKnight: return 554;
        case Unit::EliteThrowingAxeman: return 531;
        case Unit::EliteWarElephant: return 558;
        case Unit::EliteWarWagon: return 829;
        case Unit::EliteWoadRaider: return 534;
        case Unit::Huskarl: return 41;
        case Unit::Janissary: return 46;
        case Unit::Longbowman: return 8;
        case Unit::Mameluke: return 282;
        case Unit::Mangudai: return 11;
        case Unit::Missionary: return 775;
        case Unit::PlumedArcher: return 763;
        case Unit::Samurai: return 291;
        case Unit::Tarkan: return 755;
        case Unit::TeutonicKnight: return 25;
        case Unit::ThrowingAxeman: return 281;
        case Unit::Trebuchet: return 331;
        case Unit::WarElephant: return 239;
        case Unit::WarWagon: return 827;
        case Unit::WoadRaider: return 232;
        case Unit::CannonGalleon: return 420;
        case Unit::DemolitionShip: return 527;
        case Unit::EliteCannonGalleon: return 691;
        case Unit::EliteLongboat: return 533;
        case Unit::EliteTurtleShip: return 832;
        case Unit::FastFireShip: return 532;
        case Unit::FireShip: return 529;
        case Unit::FishingShip: return 13;
        case Unit::Galleon: return 442;
        case Unit::Galley: return 539;
        case Unit::HeavyDemolitionShip: return 528;
        case Unit::Longboat: return 250;
        case Unit::TradeCog: return 17;
        case Unit::TransportShip: return 545;
        case Unit::TurtleShip: return 831;
        case Unit::WarGalley: return 21;
        case Unit::TradeCart: return 128;
        case Unit::Monk: return 125;
        case Unit::BatteringRam: return 35;
        case Unit::BombardCannon: return 36;
        case Unit::CappedRam: return 422;
        case Unit::HeavyScorpion: return 542;
        case Unit::Mangonel: return 280;
        case Unit::Onager: return 550;
        case Unit::Scorpion: return 279;
        case Unit::SiegeRam: return 548;
        case Unit::SiegeOnager: return 588;
        case Unit::Camel: return 329;
        case Unit::Cavalier: return 283;
        case Unit::HeavyCamel: return 330;
        case Unit::Hussar: return 441;
        case Unit::Knight: return 38;
        case Unit::LightCavalry: return 546;
        case Unit::Paladin: return 569;
        case Unit::ScoutCavalry: return 448;
        case Unit::Villager: return 83;
        default: return -1;
        }
    }

    std::unordered_set<int> unitIds(const Unit type)
    {
        std::unordered_set<int> ids;
        switch(type) {
        case Unit::ArcherLine:
            ids.insert(unitId(Unit::Archer));
            ids.insert(unitId(Unit::Crossbowman));
            ids.insert(unitId(Unit::Arbalest));
            break;

        case Unit::CavalryArcherLine:
            ids.insert(unitId(Unit::CavalryArcher));
            ids.insert(unitId(Unit::HeavyCavalryArcher));
            break;

        case Unit::SkirmisherLine:
            ids.insert(unitId(Unit::Skirmisher));
            ids.insert(unitId(Unit::EliteSkirmisher));
            //        m_typeIds.insert(unitId(Unit::ImperialSkirmisher)); TODO: HD rise of the rajas
            break;

        case Unit::EagleWarriorLine:
            //        m_typeIds.insert(unitId(Unit::EagleScout)); // TODO the forgotten
            ids.insert(unitId(Unit::EagleWarrior));
            ids.insert(unitId(Unit::EliteEagleWarrior));
            break;

        case Unit::MilitiamanLine:
            ids.insert(unitId(Unit::Militiaman));
            ids.insert(unitId(Unit::ManAtArms));
            ids.insert(unitId(Unit::LongSwordsman));
            ids.insert(unitId(Unit::TwoHandedSwordsman));
            ids.insert(unitId(Unit::Champion));
            break;

        case Unit::SpearmanLine:
            ids.insert(unitId(Unit::Spearman));
            ids.insert(unitId(Unit::Pikeman));
            ids.insert(unitId(Unit::Halberdier));
            break;

        case Unit::BerserkLine:
            ids.insert(unitId(Unit::Berserk));
            ids.insert(unitId(Unit::EliteBerserk));
            break;

        case Unit::CataphractLine:
            ids.insert(unitId(Unit::Cataphract));
            ids.insert(unitId(Unit::EliteCataphract));
            break;

        case Unit::ChuKoNuLine:
            ids.insert(unitId(Unit::ChuKoNu));
            ids.insert(unitId(Unit::EliteChuKoNu));
            break;

        case Unit::ConquistadorLine:
            ids.insert(unitId(Unit::Conquistador));
            ids.insert(unitId(Unit::EliteConquistador));
            break;

        case Unit::HuskarlLine:
            ids.insert(unitId(Unit::Huskarl));
            ids.insert(unitId(Unit::EliteHuskarl));
            break;

        case Unit::JaguarWarriorLine:
            ids.insert(unitId(Unit::JaguarWarrior));
            ids.insert(unitId(Unit::EliteJaguarWarrior));
            break;

        case Unit::JanissaryLine:
            ids.insert(unitId(Unit::Janissary));
            ids.insert(unitId(Unit::EliteJanissary));
            break;

        case Unit::LongbowmanLine:
            ids.insert(unitId(Unit::Longbowman));
            ids.insert(unitId(Unit::EliteLongbowman));
            break;

        case Unit::MamelukeLine:
            ids.insert(unitId(Unit::Mameluke));
            ids.insert(unitId(Unit::EliteMameluke));
            break;

        case Unit::MangudaiLine:
            ids.insert(unitId(Unit::Mangudai));
            ids.insert(unitId(Unit::EliteMangudai));
            break;

        case Unit::PlumedArcherLine:
            ids.insert(unitId(Unit::PlumedArcher));
            ids.insert(unitId(Unit::ElitePlumedArcher));
            break;

        case Unit::SamuraiLine:
            ids.insert(unitId(Unit::Samurai));
            ids.insert(unitId(Unit::EliteSamurai));
            break;

        case Unit::TarkanLine:
            ids.insert(unitId(Unit::Tarkan));
            ids.insert(unitId(Unit::EliteTarkan));
            break;

        case Unit::TeutonicKnightLine:
            ids.insert(unitId(Unit::TeutonicKnight));
            ids.insert(unitId(Unit::EliteTeutonicKnight));
            break;

        case Unit::ThrowingAxemanLine:
            ids.insert(unitId(Unit::ThrowingAxeman));
            ids.insert(unitId(Unit::EliteThrowingAxeman));
            break;

        case Unit::WarElephantLine:
            ids.insert(unitId(Unit::WarElephant));
            ids.insert(unitId(Unit::EliteWarElephant));
            break;

        case Unit::WarWagonLine:
            ids.insert(unitId(Unit::WarWagon));
            ids.insert(unitId(Unit::EliteWarWagon));
            break;

        case Unit::WoadRaiderLine:
            ids.insert(unitId(Unit::WoadRaider));
            ids.insert(unitId(Unit::EliteWoadRaider));
            break;

        case Unit::CannonGalleonLine:
            ids.insert(unitId(Unit::CannonGalleon));
            ids.insert(unitId(Unit::EliteCannonGalleon));
            break;

        case Unit::DemolitionShipLine:
            // todo: hd demolition raft
            ids.insert(unitId(Unit::DemolitionShip));
            ids.insert(unitId(Unit::HeavyDemolitionShip));
            break;

        case Unit::FireShipLine:
            // todo: hd fire galley
            ids.insert(unitId(Unit::FireShip));
            ids.insert(unitId(Unit::FastFireShip));
            break;

        case Unit::GalleyLine:
            ids.insert(unitId(Unit::Galley));
            ids.insert(unitId(Unit::WarGalley));
            ids.insert(unitId(Unit::Galleon));
            break;

        case Unit::TurtleShipLine:
            ids.insert(unitId(Unit::TurtleShip));
            ids.insert(unitId(Unit::EliteTurtleShip));
            break;

        case Unit::LongboatLine:
            ids.insert(unitId(Unit::Longboat));
            ids.insert(unitId(Unit::EliteLongboat));
            break;

        case Unit::BatteringRamLine:
            ids.insert(unitId(Unit::BatteringRam));
            ids.insert(unitId(Unit::CappedRam));
            ids.insert(unitId(Unit::SiegeRam));
            break;

        case Unit::MangonelLine:
            ids.insert(unitId(Unit::Mangonel));
            ids.insert(unitId(Unit::Onager));
            ids.insert(unitId(Unit::SiegeOnager));
            break;

        case Unit::ScorpionLine:
            ids.insert(unitId(Unit::Scorpion));
            ids.insert(unitId(Unit::HeavyScorpion));
            break;

        case Unit::CamelLine:
            ids.insert(unitId(Unit::Camel));
            ids.insert(unitId(Unit::HeavyCamel));
            // todo: imperial camel hd
            break;

        case Unit::KnightLine:
            ids.insert(unitId(Unit::Knight));
            ids.insert(unitId(Unit::Cavalier));
            ids.insert(unitId(Unit::Paladin));
            break;

        case Unit::ScoutCavalryLine:
            ids.insert(unitId(Unit::ScoutCavalry));
            ids.insert(unitId(Unit::LightCavalry));
            ids.insert(unitId(Unit::Hussar));
            break;

        case Unit::MyUniqueUnit:
        case Unit::MyUniqueUnitLine:
        case Unit::MyEliteUniqueUnit:
            WARN << "Civ specific stuff not implemented yet";
            break;

        default:
            ids.insert(unitId(type));
            break;
        }
        return ids;
    }

    std::unordered_set<int> unitIds(const Building type)
    {
        std::unordered_set<int> ids;
        switch(type) {
        case Building::WatchTowerLine:
        case Building::WatchTower: // apparently a bug that WatchTower means the entire upgrade line
            ids.insert(unitId(Building::WatchTower));
            ids.insert(unitId(Building::GuardTower));
            ids.insert(unitId(Building::Keep));
            break;
        default:
            ids.insert(unitId(type));
            break;
        }

        return ids;
    }

    std::unordered_set<int> unitIds(const WallType type)
    {
        std::unordered_set<int> ids;

        switch(type) {
        case WallType::StoneWallLine:
            ids.insert(unitId(WallType::StoneWall));
            ids.insert(unitId(WallType::FortifiedWall));
            break;
        default:
            ids.insert(unitId(type));
            break;
        }

        return ids;
    }

} // namespace ai
