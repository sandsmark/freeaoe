#pragma once

#include "core/Types.h"
#include "global/EventListener.h"

#include "mechanics/IState.h"
#include "mechanics/UnitManager.h"
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

class ActionPanel : public IState, public EventListener
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
    ~ActionPanel();

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
    void onActionsChanged() { m_buttonsDirty = true; }
    void onPlayerResourceChanged(Player *player, const genie::ResourceType type, float newValue) override;

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
    std::weak_ptr<Player> m_humanPlayer;
    int m_humanPlayerId = -1;
    ScreenRect m_rect;

    std::unordered_map<Command, sf::Texture> m_commandIcons;
    std::unordered_map<int, sf::Texture> m_unitIcons;
    std::unordered_map<int, sf::Texture> m_buildingIcons;
    std::unordered_map<int, sf::Texture> m_researchIcons;

    int m_currentPage = 3;
    int m_buttonOffset = 0;

    // TODO: should be weak pointer, this is STRONK shared ptr
    UnitSet m_selectedUnits;
    UnitManager::State m_unitManagerState = UnitManager::State::Default;

    std::vector<InterfaceButton> currentButtons;
    bool m_dirty = true;
    bool m_buttonsDirty = true;
};

inline LogPrinter &operator <<(LogPrinter &os, const ActionPanel::Command &cmd)
{
    os << "ActionPanel::Command(" << int(cmd);
    switch (cmd) {
    case ActionPanel::Command::Cancel: os << "Cancel"; break;
    case ActionPanel::Command::AbortPatrol: os << "AbortPatrol"; break;
    case ActionPanel::Command::Ungarrison: os << "Ungarrison"; break;
    case ActionPanel::Command::Stop: os << "Stop"; break;
    case ActionPanel::Command::Group: os << "Group"; break;
    case ActionPanel::Command::Ungroup: os << "Ungroup"; break;
    case ActionPanel::Command::Patrol: os << "Patrol"; break;
    case ActionPanel::Command::Guard: os << "Guard"; break;
    case ActionPanel::Command::Follow: os << "Follow"; break;
    case ActionPanel::Command::Aggressive: os << "Aggressive"; break;
    case ActionPanel::Command::Defensive: os << "Defensive"; break;
    case ActionPanel::Command::StandGround: os << "StandGround"; break;
    case ActionPanel::Command::Pack: os << "Pack"; break;
    case ActionPanel::Command::Unpack: os << "Unpack"; break;
    case ActionPanel::Command::Convert: os << "Convert"; break;
    case ActionPanel::Command::Heal: os << "Heal"; break;
    case ActionPanel::Command::PickUpRelic: os << "PickUpRelic"; break;
    case ActionPanel::Command::Disembark: os << "Disembark"; break;
    case ActionPanel::Command::CollectWood: os << "CollectWood"; break;
    case ActionPanel::Command::CollectFood: os << "CollectFood"; break;
    case ActionPanel::Command::CollectGold: os << "CollectGold"; break;
    case ActionPanel::Command::CollectStone: os << "CollectStone"; break;
    case ActionPanel::Command::BuyFood: os << "BuyFood"; break;
    case ActionPanel::Command::BuyStone: os << "BuyStone"; break;
    case ActionPanel::Command::SellFood: os << "SellFood"; break;
    case ActionPanel::Command::SellWood: os << "SellWood"; break;
    case ActionPanel::Command::SellStone: os << "SellStone"; break;
    case ActionPanel::Command::Trade: os << "Trade"; break;
    case ActionPanel::Command::Repair: os << "Repair"; break;
    case ActionPanel::Command::LootMaybe: os << "LootMaybe"; break;
    case ActionPanel::Command::BuildCivilian: os << "BuildCivilian"; break;
    case ActionPanel::Command::BuildMilitary: os << "BuildMilitary"; break;
    case ActionPanel::Command::NextPage: os << "NextPage"; break;
    case ActionPanel::Command::BuildFishTrap: os << "BuildFishTrap"; break;
    case ActionPanel::Command::SignalFlare: os << "SignalFlare"; break;
    case ActionPanel::Command::SquareFormation: os << "SquareFormation"; break;
    case ActionPanel::Command::RotateFormationRight: os << "RotateFormationRight"; break;
    case ActionPanel::Command::RotateFormationLeft: os << "RotateFormationLeft"; break;
    case ActionPanel::Command::MoveFormationFrontToBack: os << "MoveFormationFrontToBack"; break;
    case ActionPanel::Command::DisbandFormation: os << "DisbandFormation"; break;
    case ActionPanel::Command::LineFormation: os << "LineFormation"; break;
    case ActionPanel::Command::AttackWithSword: os << "AttackWithSword"; break;
    case ActionPanel::Command::JumpOverWall: os << "JumpOverWall"; break;
    case ActionPanel::Command::BoxFormation: os << "BoxFormation"; break;
    case ActionPanel::Command::HordeFormation: os << "HordeFormation"; break;
    case ActionPanel::Command::SetRallyPoint: os << "SetRallyPoint"; break;
    case ActionPanel::Command::RemoveRallyPoint: os << "RemoveRallyPoint"; break;
    case ActionPanel::Command::CloseGate: os << "CloseGate"; break;
    case ActionPanel::Command::OpenGate: os << "OpenGate"; break;
    case ActionPanel::Command::RingTownBell: os << "RingTownBell"; break;
    case ActionPanel::Command::NoAttack: os << "NoAttack"; break;
    case ActionPanel::Command::StandGroundEnabled: os << "StandGroundEnabled"; break;
    case ActionPanel::Command::DefensiveEnabled: os << "DefensiveEnabled"; break;
    case ActionPanel::Command::AggressiveEnabled: os << "AggressiveEnabled"; break;
    case ActionPanel::Command::NoAttackEnabled: os << "NoAttackEnabled"; break;
    case ActionPanel::Command::PatrolEnabled: os << "PatrolEnabled"; break;
    case ActionPanel::Command::GuardEnabled: os << "GuardEnabled"; break;
    case ActionPanel::Command::FollowEnabled: os << "FollowEnabled"; break;
    case ActionPanel::Command::ResearchSpies: os << "ResearchSpies"; break;
    case ActionPanel::Command::Kill: os << "Kill"; break;
    case ActionPanel::Command::AttackGround: os << "AttackGround"; break;
    case ActionPanel::Command::AbortTownBell: os << "AbortTownBell"; break;
    case ActionPanel::Command::FlankFormation: os << "FlankFormation"; break;
    case ActionPanel::Command::SpreadOutFormation: os << "SpreadOutFormation"; break;
    case ActionPanel::Command::UngarrisonCivilian: os << "UngarrisonCivilian"; break;
    case ActionPanel::Command::NormalFormationEnabled: os << "NormalFormationEnabled"; break;
    case ActionPanel::Command::BoxFormationEnabled: os << "BoxFormationEnabled"; break;
    case ActionPanel::Command::FlankFormationEnabled: os << "FlankFormationEnabled"; break;
    case ActionPanel::Command::SpreadOutFormationEnabled: os << "SpreadOutFormationEnabled"; break;
    case ActionPanel::Command::IconCount: os << "IconCount"; break;
    case ActionPanel::Command::PreviousPage: os << "PreviousPage"; break;
    case ActionPanel::Command::Garrison: os << "Garrison"; break;
    case ActionPanel::Command::Undefined: os << "Undefined"; break;
    default: os << "Invalid"; break;
    }
    os << ")";
    return os;
}

