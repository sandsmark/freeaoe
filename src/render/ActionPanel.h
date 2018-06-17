#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include <mechanics/IState.h>
#include <mechanics/Player.h>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <unordered_map>
#include <unordered_set>

class Entity;
class Unit;
class SfmlRenderTarget;
class UnitManager;
typedef std::unordered_set<std::shared_ptr<Unit>> UnitSet;

class ActionPanel : public IState
{
public:
    enum class Command : int {
        Cancel,
        AbortPatrol,
        Ungarrison,
        Stop,
        Group,
        Ungroup,
        Patrol,
        Guard,
        Follow,
        Aggressive,
        Defensive,
        StandGround,
        Pack,
        Unpack,
        Convert,
        Heal,
        PickUpRelic,
        Disembark,
        CollectWood,
        CollectFood,
        CollectGold,
        CollectStone,
        BuyFood,
        BuyStone,
        SellFood,
        SellWood,
        SellStone,
        Trade,
        Repair,
        LootMaybe,
        BuildCivilian,
        BuildMilitary,
        NextPage,
        BuildFishTrap,
        SignalFlare,
        SquareFormation,
        RotateFormationRight,
        RotateFormationLeft,
        MoveFormationFrontToBack,
        DisbandFormation,
        NormalFormation,
        AttackWithSword,
        JumpOverWall,
        BoxFormation,
        LooseFormation,
        SetRallyPoint,
        RemoveRallyPoint,
        OpenGate,
        CloseGate,
        RingTownBell,
        SwordInStone,
        StandGroundEnabled,
        DefensiveEnabled,
        AggressiveEnabled,
        SwordInStoneEnabled,
        PatrolEnabled,
        GuardEnabled,
        FollowEnabled,
        EyeThing,
        Kill,
        AttackGround,
        AbortTownBell,
        FlankFormation,
        SpreadOutFormation,
        GarrisonCivilian,
        NormalFormationEnabled,
        BoxFormationEnabled,
        FlankFormationEnabled,
        SpreadOutFormationEnabled,
        IconCount,

        PreviousPage,

        Undefined
    };

    ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    ActionPanel() = delete;

    bool init() override;
    void handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

    void setUnitManager(const std::shared_ptr<UnitManager> &unitManager);
    void setHumanPlayer(const Player::Ptr &player);

    ScreenRect rect() const;

    void releaseButtons();

private:
    struct InterfaceButton {
        enum Type {
            CreateUnit,
            CreateBuilding,
            Research,
            Other
        };

        int targetId = 0;
        int iconId = 0;

        Command action = Command::Undefined;

        int index = 0;
        bool pressed = false;
        int interfacePage = 0;

        Type type = Other;
    };

    void updateButtons();
    void addCreateButtons(const std::shared_ptr<Unit> &unit);
    void addCreateBuildingButtons();
    void handleButtonClick(const InterfaceButton &button);

    ScreenPos buttonPosition(const int index) const;
    ScreenRect buttonRect(const int index) const;

    std::shared_ptr<SfmlRenderTarget> m_renderTarget;
    std::shared_ptr<UnitManager> m_unitManager;
    Player::Ptr m_humanPlayer;
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

#endif // ACTIONPANEL_H
