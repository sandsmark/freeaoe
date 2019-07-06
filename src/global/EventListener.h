#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <cstddef>

#include "core/Types.h"

struct Unit;
struct Player;

struct EventListener
{
public:
    EventListener();
    virtual ~EventListener();

    virtual void onUnitCreated(Unit *unit)
        { (void)unit; }

    virtual void onUnitDying(Unit *unit)
        { (void)unit; }

    virtual void onUnitSelected(Unit *unit)
        { (void)unit; }

    virtual void onUnitOwnerChanged(Unit *unit, int oldPlayerId, int newPlayerId)
        { (void)unit; (void)oldPlayerId; (void)newPlayerId; }

    virtual void onUnitCaptured(Unit *unit, int oldPlayerId, int newPlayerId)
        { (void)unit; (void)oldPlayerId; (void)newPlayerId; }

    virtual void onUnitMoved(Unit *unit, const MapPos &newPosition)
        { (void)unit; (void)newPosition; }

    virtual void onUnitGarrisoned(Unit *unit, Unit *garrisonedIn)
        { (void)unit; (void)garrisonedIn; }

    virtual void onUnitGotTarget(Unit *unit, Unit *targetUnit)
        { (void)unit; (void)targetUnit; }

    virtual void onUnitDelivered(Unit *unit, Unit *deliveredUnit, Unit *targetUnit)
        { (void)unit; (void)deliveredUnit; (void)targetUnit; }

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
};

#endif // EVENTLISTENER_H
