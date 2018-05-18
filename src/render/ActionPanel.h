#ifndef ACTIONPANEL_H
#define ACTIONPANEL_H

#include <mechanics/IState.h>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <unordered_map>
#include <unordered_set>

class Entity;
class Unit;
class SfmlRenderTarget;
class EntityManager;
typedef std::unordered_set<std::shared_ptr<Entity>> EntitySet;

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

        PreviousPage
    };

    ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    ActionPanel() = delete;

    bool init() override;
    void handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

    void setEntityManager(const std::shared_ptr<EntityManager> &entityManager);

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

        int createId = 0;
        int iconId = 0;

        Command action;

        int index = 0;
        bool pressed = false;
        int interfacePage = 0;

        Type type = Other;
    };

    void updateButtons();
    void addCreateButtons(const std::shared_ptr<Unit> &unit);

    ScreenPos buttonPosition(const int index) const;
    ScreenRect buttonRect(const int index) const;

    std::shared_ptr<SfmlRenderTarget> m_renderTarget;
    std::shared_ptr<EntityManager> m_entityManager;
    ScreenRect m_rect;

    std::unordered_map<Command, sf::Texture> m_commandIcons;
    std::unordered_map<int, sf::Texture> m_unitIcons;
    std::unordered_map<int, sf::Texture> m_buildingIcons;
    std::unordered_map<int, sf::Texture> m_researchIcons;

    int m_currentPage = 3;
    int m_buttonOffset = 0;

    EntitySet m_selectedEntities;

    std::vector<InterfaceButton> currentButtons;
    bool m_dirty = true;
};

#endif // ACTIONPANEL_H
