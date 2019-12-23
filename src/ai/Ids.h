#pragma once
#include "gen/enums.h"
namespace ai
{
    enum class OtherUnits {
        Gate
    };
    int unitId(const OtherUnits &unit) {
        switch (unit) {
        case OtherUnits::Gate: return 487;
        default: return -1;
        }
    }
    int unitId(const WallType &wall) {
        switch (wall) {
        case WallType::FortifiedWall: return 155;
        case WallType::PalisadeWall: return 72;
        case WallType::StoneWall: return 117;
        default: return -1;
        }
    }

    int unitId(const Building &building) {
        switch(building) {
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

    int unitId(const Unit &unit) {
        switch(unit) {
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
};
