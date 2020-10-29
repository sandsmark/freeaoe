#pragma once

namespace SLP
{
    static constexpr int Cursors = 51000;
    static constexpr int Commands = 50721;

namespace AoE2
{
    static constexpr int Units = 50730;
    static constexpr int Technology = 50729;
    static constexpr int Buildings = 50705;
}

// From http://swgb.heavengames.com/downloads/showfile.php?fileid=2762
namespace SWGB
{
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



namespace AoE2 {
enum UnitID {
    // For creating normal games
    TownCenter = 109,

    FemaleVillager = 293,

    MaleVillager = 83,
    MaleLumberjack = 123,
    MaleStoneMiner = 124,
    MaleHunter = 122,
    MaleFarmer = 259,
    MaleForager = 120,
    MaleFisherman = 56,
    MaleGoldMiner = 579,
    MaleShepherd = 592,
    MaleBuilder = 118,
    MaleRepairer = 156,

    Docket = 45,
    Castle = 82,
    Market = 84,

    ArcheryRange = 87,
    Archer = 4,

    Barracks = 12,
    Monastery = 104,
    SiegeWorkshop = 49,
    Stable = 101,

    Dock = 45,

    // Special handling
    Mill = 68,
    LumberCamp = 562,
    MiningCamp = 584,

    // For convenience when creating
    PalisadeWall = 72,
    StoneWall = 117,
    FortifiedWall = 155,
    Gate = 487,

    // Farms are very special
    Farm = 50,

    // Nice to have because they are fun
    Cobra = 748,
    VMDL = 206,
    FuriousTheMonkeyBoy = 860,
    StormyDog = 862,

    // For replacements when loading scenarios, from danielpereira on aok.heavengames.com:
    //   IDs 768/770 should be kept disabled. They are used as a layer to
    //   enable the special Spanish Cannon Galleon bonuses
    //   If you check in the Technologies data in the .dat, you'll see
    //   that unit 768 is enabled for Spanish instead of the usual
    //   Cannon Galleon, and that the Elite Cannon Galleon technology
    //   upgrades this unit to ID 770.
    //   And, when I said that this unit is used as a layer,
    //   I mean that, when the game loads this unit,
    //   it replaces it with a Cannon Galleon and applies the Spanish bonuses
    // http://aok.heavengames.com/cgi-bin/forums/display.cgi?action=st&fn=4&tn=42049&st=96
    SpanishCannonGalleon = 768,
    EliteSpanishCannonGalleon = 770,
    CannonGalleon = 420,
    EliteCannonGalleon = 691
}; // enum UnitID

}
