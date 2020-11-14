#pragma once

struct MapPos;
struct Player;
struct Unit;

#include <stdint.h>
#include <string>

namespace genie {
enum class ResourceType : int16_t;
}

/**
 * @brief For classes that want to monitor for events, e. g. for scenarios or AI
 */

struct EventListener
{
public:
    EventListener();
    virtual ~EventListener();

protected:
    friend class EventManager;

    virtual void onUnitCreated(Unit *unit)
        { (void)unit; }

    virtual void onUnitDying(Unit *unit)
        { (void)unit; }

    virtual void onUnitSelected(Unit *unit)
        { (void)unit; }

    virtual void onUnitDeselected(const Unit *unit)
        { (void)unit; }

    virtual void onUnitOwnerChanged(Unit *unit, int oldPlayerId, int newPlayerId)
        { (void)unit; (void)oldPlayerId; (void)newPlayerId; }

    virtual void onUnitCaptured(Unit *unit, int oldPlayerId, int newPlayerId)
        { (void)unit; (void)oldPlayerId; (void)newPlayerId; }

    virtual void onUnitMoved(Unit *unit, const MapPos &oldTile, const MapPos &newTile)
        { (void)unit; (void)oldTile; (void)newTile; }

    virtual void onUnitGarrisoned(Unit *unit, Unit *garrisonedIn)
        { (void)unit; (void)garrisonedIn; }

    virtual void onUnitGotTarget(Unit *unit, Unit *targetUnit)
        { (void)unit; (void)targetUnit; }

    virtual void onUnitDelivered(Unit *unit, Unit *deliveredUnit, Unit *targetUnit)
        { (void)unit; (void)deliveredUnit; (void)targetUnit; }

    virtual void onUnitChangedGroup(Unit *unit, int oldGroup, int newGroup)
        { (void)unit; (void)oldGroup; (void)newGroup; }


    virtual void onResearchStarted(Player *player, int researchId)
        { (void)player; (void)researchId; }

    virtual void onResearchCompleted(Player *player, int researchId)
        { (void)player; (void)researchId; }

    virtual void onPlayerDefeated(Player *player)
        { (void)player; }

    virtual void onAiSignal(Player *player, int signalId)
        { (void)player; (void)signalId; }

    virtual void onAttributeChanged(Player *player, int attributeId, float newValue)
        { (void)player; (void)attributeId; (void)newValue; }

    virtual void onUnitDiscovered(Player *player, Unit *unit)
        { (void)player; (void)unit; }

    virtual void onUnitDisappeared(Player *player, Unit *unit)
        { (void)player; (void)unit; }

    virtual void onPlayerResourceChanged(Player *player, const genie::ResourceType type, float newValue)
        { (void)player; (void)type; (void)newValue; }

    virtual void onResourceBought(const genie::ResourceType type, const int amount)
        { (void)type; (void)amount; }

    virtual void onResourceSold(const genie::ResourceType type, const int amount)
        { (void)type; (void)amount; }

    virtual void onTradingPriceChanged(const genie::ResourceType type, const int newPrice)
        { (void)type; (void)newPrice; }

    virtual void onTileDiscovered(const int playerID, const int tileX, const int tileY)
        { (void)playerID; (void)tileX; (void)tileY; }

    virtual void onTileHidden(const int playerID, const int tileX, const int tileY)
        { (void)playerID; (void)tileX; (void)tileY; }

    virtual void onChatMessage(const int sourcePlayer, const int targetPlayer, const std::string &message)
        { (void)sourcePlayer; (void)targetPlayer; (void)message; }
};

