#pragma once

#include "core/Types.h"

#include "mechanics/IState.h"
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core/Types.h"

struct Entity;
struct Unit;

struct Player;
using PlayerPtr = std::shared_ptr<Player>;

class SfmlRenderTarget;
class UnitManager;
namespace genie {
class Unit;
}  // namespace genie
namespace sf {
class Event;
class Texture;
}  // namespace sf

typedef std::vector<std::shared_ptr<Unit>> UnitVector;
typedef std::unordered_set<std::shared_ptr<Unit>> UnitSet;

namespace genie {
class Tech;
class Unit;
}

class ActionPanel : public IState
{
public:
    enum class Technology {
        CropRotation = 1,
        HeavyPlow = 2,
        HorseCollar = 3,
        Banking = 4,
        Cartography = 5,
        Sappers = 6,
        Loom = 7,
        Coinage = 8,
        WarGalley = 9,
        CanonGalleon = 10,
        Husbandry = 11,
        Faith = 12,
        Chemistry = 13,
        Masonry = 14,
        Architecture = 15,
        GoldMining = 16,
        Keep = 17,
        Forging = 18,
        IronCasting = 19,
        Spies = 20,
        ChainMailArmor = 21,
        BlastFurnace = 22,
        SomeGunBullets = 23,
        ChainBardingArmor = 24,
        IdkCannonBalls = 25,
        Ballistics = 26,
        EliteSkirmisher = 27,
        CappedRam = 28,
        FeudalAge = 29,
        CrossbowMan = 30,
        ImperialAge = 31,
        CastleAge = 32,
        Fletching = 33,
        BoringAxe = 34,
        Pikeman = 35,
        BodkinArrow = 36,
        HeavyScorpion = 37,
        Bracer = 38,
        ExplodingCanon = 39,
        HeavyDemolitionShip = 40,
        Handcart = 41,
        UglyLongboat = 42,
        Champion = 43,
        LightCavalry = 44,
        FortifiedWall = 45,
        Paladin = 46,
        LongSwordsman = 47,
        BombardTower = 48,
        LeatherArcherArmor = 49,
        PaddedArcherArmor = 50,
        HeavyCavalryArcher = 51,
        RingArcherArmor = 52,
        Arbalest = 53,
        TwoHandedSwordsman = 54,
        TrebuchetThing = 55,
        HeavyCamel = 56,
        Guilds = 57,
        Onager = 58,
        TreadmillCrane = 59,
        Galleon = 60,
        GoldShaftMining = 61,
        MurderHoles = 62,
        PlateMailArmor = 63,
        ScaleMailArmor = 64,
        ScaleBardingArmor = 65,
        PlateBardingArmor = 66,
        IdkTinyScorpion = 67,
        Tracking = 68,
        DoubleBitAxe = 69,
        TownWatch = 70,
        Fervor = 71,
        BowSaw = 72,
        GuardTower = 73,
        MapAndInkwellAndCirclething = 74,
        Cavalier = 75,
        Wheelbarrow = 76,
        Squires = 77,
        TwoManSaw = 78,
        BlockPrinting = 79,
        Sanctity = 80,
        Illumination = 81,
        ManAtArms = 82,
        SiegeRam = 83,
        StoneMining = 84,
        StoneShaftMining = 85,
        TownPatrol = 86,
        Redemption = 87,
        Conscription = 88,
        IdkShadowyShipAtSea = 89,
        Atonement = 90,
        Shipwright = 91,
        SiegeOnager = 92,
        DryDock = 93,
        Careening = 94,
        SiegeEngineers = 95,
        EliteCanonGaleon = 96,
        Hoardings = 97,
        SiegeEngineers2 = 98,
        IdkMedal = 99,
        HeatedShot = 100,
        UniqueTech2 = 101,
        Halberdier = 102,
        Theocracy = 103,
        Heresy = 104,
        IdkCavalryArcher = 105,
        Bloodlines = 106,
        Caravan = 107,
        ThumbRing = 108,
        EagleWarrior = 109,
        HerbalMedicine = 110,
        Unavailable = 111,
        PointingSigns = 112,
    };

    enum class Command : int {
        Cancel = 0,
        AbortPatrol = 1,
        Ungarrison = 2,
        Stop = 3,
        Group = 4,
        Ungroup = 5,
        Patrol = 6,
        Guard = 7,
        Follow = 8,
        Aggressive = 9,
        Defensive = 10,
        StandGround = 11,
        Pack = 12,
        Unpack = 13,
        Convert = 14,
        Heal = 15,
        PickUpRelic = 16,
        Disembark = 17,
        CollectWood = 18,
        CollectFood = 19,
        CollectGold = 20,
        CollectStone = 21,
        BuyFood = 22,
        BuyStone = 23,
        SellFood = 24,
        SellWood = 25,
        SellStone = 26,
        Trade = 27,
        Repair = 28,
        LootMaybe = 29,
        BuildCivilian = 30,
        BuildMilitary = 31,
        NextPage = 32,
        BuildFishTrap = 33,
        SignalFlare = 34,
        SquareFormation = 35,
        RotateFormationRight = 36,
        RotateFormationLeft = 37,
        MoveFormationFrontToBack = 38,
        DisbandFormation = 39,
        LineFormation = 40,
        AttackWithSword = 41,
        JumpOverWall = 42,
        BoxFormation = 43,
        HordeFormation = 44,
        SetRallyPoint = 45,
        RemoveRallyPoint = 46,
        CloseGate = 47,
        OpenGate = 48,
        RingTownBell = 49,
        NoAttack = 50,
        StandGroundEnabled = 51,
        DefensiveEnabled = 52,
        AggressiveEnabled = 53,
        NoAttackEnabled = 54,
        PatrolEnabled = 55,
        GuardEnabled = 56,
        FollowEnabled = 57,
        ResearchSpies = 58,
        Kill = 59,
        AttackGround = 60,
        AbortTownBell = 61,
        FlankFormation = 62,
        SpreadOutFormation = 63,
        UngarrisonCivilian = 64,
        NormalFormationEnabled = 65,
        BoxFormationEnabled = 66,
        FlankFormationEnabled = 67,
        SpreadOutFormationEnabled = 68,
        IconCount = 69,

        // Special ones not actually in the SLP
        PreviousPage,
        Garrison,

        Undefined
    };

    ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    ActionPanel() = delete;

    bool init() override;
    bool handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

    void setUnitManager(const std::shared_ptr<UnitManager> &unitManager);
    void setHumanPlayer(const PlayerPtr &player);

    ScreenRect rect() const;

    void releaseButtons();
//    void setAttackStance(const Unit::Stance stance) const;

    static const std::string &helpTextId(const Command icon);

private:
    struct InterfaceButton {
        enum Type {
            CreateUnit,
            CreateBuilding,
            Research,
            AttackStance,
            Other
        };

        union {
            const genie::Unit *unit = nullptr;
            const genie::Tech *tech;
        };

        int iconId = 0;

        Command action = Command::Undefined;

        int index = 0;
        bool pressed = false;
        int interfacePage = 0;

        bool showBorder = true;

        Type type = Other;
    };

    void updateButtons();
    void addCreateButtons(const std::shared_ptr<Unit> &unit);
    void addResearchButtons(const std::shared_ptr<Unit> &unit);
    void addMilitaryButtons(const std::shared_ptr<Unit> &unit);
    void handleButtonClick(const InterfaceButton &button);

    ScreenPos buttonPosition(const int index) const;
    ScreenRect buttonRect(const int index) const;

    std::shared_ptr<SfmlRenderTarget> m_renderTarget;
    std::shared_ptr<UnitManager> m_unitManager;
    PlayerPtr m_humanPlayer;
    ScreenRect m_rect;

    std::unordered_map<Command, sf::Texture> m_commandIcons;
    std::unordered_map<int, sf::Texture> m_unitIcons;
    std::unordered_map<int, sf::Texture> m_buildingIcons;
    std::unordered_map<int, sf::Texture> m_researchIcons;

    int m_currentPage = 3;
    int m_buttonOffset = 0;

    UnitSet m_selectedUnits;

    std::vector<InterfaceButton> currentButtons;
    bool m_dirty = true;
};

inline std::ostream &operator <<(std::ostream &os, const ActionPanel::Command &cmd) {
    os << "ActionPanel::Command(" << int(cmd);
//    switch (cmd) {
//        case Cancel:
//            os << "Cancel"; break;
//        case AbortPatrol:
//            os << "AbortPatrol"; break;
//        case Ungarrison:
//            os << "Ungarrison"; break;
//        case Stop:
//            os << "Stop"; break;
//        case Group:
//            os << "Group"; break;
//        case Ungroup:
//            os << "Ungroup"; break;
//        case Patrol:
//            os << "Patrol"; break;
//        case Guard:
//            os << "Guard"; break;
//        case Follow:
//            os << "Follow"; break;
//        case Aggressive:
//            os << "Aggressive"; break;
//        case Defensive:
//            os << "Defensive"; break;
//        case StandGround:
//            os << "StandGround"; break;
//        case Pack:
//            os << "Pack"; break;
//        case Unpack:
//            os << "Unpacl"; break;
//        case Convert:
//            os << "Convert"; break;
//        case Heal:
//            os << "Heal"; break;
//        case PickUpRelic:
//            os << "PickUpRelic"; break;
//        case Disembark:
//            os << "Disembark"; break;
//        case CollectWood:
//            os << "CollectWood"; break;
//        case CollectFood:
//            os << "CollectFood"; break;
//        case CollectGold:
//            os << "CollectGold"; break;
//        case CollectStone:
//            os << "CollectStone"; break;
//        case BuyFood:
//            os << "BuyFood"; break;
//        case BuyStone:
//            os << "BuyStone"; break;
//        case SellFood:
//            os << "SellFood"; break;
//        case SellWood:
//            os << "SellWood"; break;
//        case SellStone:
//            os << "SellStone"; break;
//        case Trade:
//            os << "Trade"; break;
//        case Repair:
//            os << "Repair"; break;
//        case LootMaybe:
//            os << "LootMaybe"; break;
//        case BuildCivilian:
//            os << "BuildCivilian"; break;
//        case BuildMilitary:
//            os << "BuildMilitary"; break;
//        case NextPage:
//            os << "NextPage"; break;
//        case BuildFishTrap:
//            os << "BuildFishTrap"; break;
//        case SignalFlare:
//            os << "SignalFlare"; break;
//        case SquareFormation:
//            os << "SquareFormation"; break;
//        case RotateFormationRight:
//            os << "RotateFormationRight"; break;
//        case RotateFormationLeft:
//            os << "RotateFormationLeft"; break;
//        case MoveFormationFrontToBack:
//            os << "MoveFormationFrontToBack"; break;
//        case DisbandFormation:
//            os << "DisbandFormation"; break;
//        case NormalFormation:
//            os << "NormalFormation"; break;
//        case AttackWithSword:
//            os << "AttackWithSword"; break;
//        case JumpOverWall:
//            os << "JumpOverWall"; break;
//        case BoxFormation:
//            os << "BoxFormation"; break;
//        case LooseFormation:
//            os << "LooseFormation"; break;
//        case SetRallyPoint:
//            os << "SetRallyPoint"; break;
//        case RemoveRallyPoint:
//            os << "RemoveRallyPoint"; break;
//        case OpenGate:
//            os << "OpenGate"; break;
//        case CloseGate:
//            os << "CloseGate"; break;
//        case RingTownBell:
//            os << "RingTownBell"; break;
//        case SwordInStone:
//            os << "SwordInStone"; break;
//        case StandGroundEnabled:
//            os << "StandGroundEnabled"; break;
//        case DefensiveEnabled:
//            os << "DefensiveEnabled"; break;
//        case AggressiveEnabled:
//            os << "AggressiveEnabled"; break;
//        case SwordInStoneEnabled:
//            os << "SwordInStoneEnabled"; break;
//        case PatrolEnabled:
//            os << "PatrolEnabled"; break;
//        case GuardEnabled:
//            os << "GuardEnabled"; break;
//        case FollowEnabled:
//            os << "FollowEnabled"; break;
//        case EyeThing:
//            os << "EyeThing"; break;
//        case Kill:
//            os << "Kill"; break;
//        case AttackGround:
//            os << "AttackGround"; break;
//        case AbortTownBell:
//            os << "AbortTownBell"; break;
//        case FlankFormation:
//            os << "FlankFormation"; break;
//        case SpreadOutFormation:
//            os << "SpreadOutFormation"; break;
//        case GarrisonCivilian:
//            os << "GarrisonCivilian"; break;
//        case NormalFormationEnabled:
//            os << "NormalFormationEnabled"; break;
//        case BoxFormationEnabled:
//            os << "BoxFormationEnabled"; break;
//        case FlankFormationEnabled:
//            os << "FlankFormationEnabled"; break;
//        case SpreadOutFormationEnabled:
//            os << "SpreadOutFormationEnabled"; break;
//        case IconCount:
//            os << "IconCount"; break;
//        case PreviousPage:
//            os << "PreviousPage"; break;
//        default:
//            os << "Invalid";
//            break;
//    }
    os << ")";
    return os;
}

