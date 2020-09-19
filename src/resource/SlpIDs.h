#pragma once

namespace SLP {
static constexpr int Cursors = 51000;
static constexpr int Commands = 50721;

namespace AoE2 {
static constexpr int Units = 50730;
static constexpr int Technology = 50729;
static constexpr int Buildings = 50705;
};

// From http://swgb.heavengames.com/downloads/showfile.php?fileid=2762
namespace SWGB {

enum Civilization : int {
    GalacticEmpire = 1,
    Gungans = 2,
    RebelAlliance = 3,
    RoyalNaboo = 4,
    TradeFederation = 5,
    Wookies = 6,

    MaxCiv = 7
};

static constexpr int BuildingsOffset = 50705;
static constexpr int UnitsOffset = 50733;
static constexpr int TechnologyOffset = 50689;

static constexpr int PlayButtons = 53008;
static constexpr int LagIndicator = 53011;

static constexpr int NumberOfCommandSLPs = 3;
static constexpr int CommandSLPOffset = 50788;

namespace CC {

static constexpr int BuildingsOffset = 53240;
static constexpr int UnitsOffset = 53250;
static constexpr int TechnologyOffset = 53260;

enum Civilization : int {
    GalacticRepublic = 7,
    Confederacy = 8,
    MaxCiv = 9
};

} //namespace CC
} //namespace SWGB
} // namespace SLP

