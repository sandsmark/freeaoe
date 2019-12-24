#include "EventManager.h"

#include "EventListener.h"

#include "core/Types.h"

struct MapPos;

EventManager::EventManager()
{

}

EventManager *EventManager::instance()
{
    static EventManager inst;
    return &inst;
}


void EventManager::registerListener(EventListener *listener, const EventManager::EventType type)
{
    instance()->m_entityEventListeners[type].push_back(listener);
}

void EventManager::deregisterListener(EventListener *listener)
{
    for (int type = 0; type<EventTypeCount; type++) {
        deregisterListener(listener, EventType(type));
    }
}

void EventManager::onListenerDestroyed(EventListener *listener)
{
    deregisterListener(listener);
}

void EventManager::deregisterListener(EventListener *listener, const EventManager::EventType type)
{
    instance()->m_entityEventListeners[type].remove(listener);
}

void EventManager::unitCreated(Unit *unit)
{
    call(UnitCreated, [=](EventListener *l) { l->onUnitCreated(unit); });
}

void EventManager::unitDying(Unit *unit)
{
    call(UnitDestroyed, [=](EventListener *l) { l->onUnitDying(unit); });
}

void EventManager::unitSelected(Unit *unit)
{
    call(UnitSelected, [=](EventListener *l) { l->onUnitSelected(unit); });
}

void EventManager::unitDeselected(const Unit *unit)
{
    call(UnitSelected, [=](EventListener *l) { l->onUnitDeselected(unit); });
}

void EventManager::unitOwnerChanged(Unit *unit, int oldPlayerId, int newPlayerId)
{
    call(UnitChangedOwner, [&](EventListener *l) { l->onUnitOwnerChanged(unit, oldPlayerId, newPlayerId); });
}

void EventManager::unitCaptured(Unit *unit, int oldPlayerId, int newPlayerId)
{
    call(UnitCaptured, [&](EventListener *l) { l->onUnitCaptured(unit, oldPlayerId, newPlayerId); });
}

void EventManager::unitMoved(Unit *unit, const MapPos &oldtile, const MapPos &newTile)
{
    call(UnitMoved, [=](EventListener *l) { l->onUnitMoved(unit, oldtile, newTile); });
}

void EventManager::unitGarrisoned(Unit *unit, Unit *garrisonedIn)
{
    call(UnitGarrisoned, [=](EventListener *l) { l->onUnitGarrisoned(unit, garrisonedIn); });
}

void EventManager::unitGotTarget(Unit *unit, Unit *targetUnit)
{
    call(UnitGotTarget, [=](EventListener *l) { l->onUnitGotTarget(unit, targetUnit); });
}

void EventManager::unitDelivered(Unit *unit, Unit *deliveredUnit, Unit *targetUnit)
{
    call(UnitDeliveredUnit, [=](EventListener *l) { l->onUnitDelivered(unit, deliveredUnit, targetUnit); });
}

void EventManager::unitChangedGroup(Unit *unit, int oldGroup, int newGroup)
{
    call(UnitChangedGroup, [=](EventListener *l) { l->onUnitChangedGroup(unit, oldGroup, newGroup); });
}

void EventManager::researchStarted(Player *player, int researchId)
{
    call(ResearchStarted, [=](EventListener *l) { l->onResearchStarted(player, researchId); });
}

void EventManager::researchCompleted(Player *player, int researchId)
{
    call(ResearchComplete, [=](EventListener *l) { l->onResearchCompleted(player, researchId); });
}

void EventManager::playerDefeated(Player *player)
{
    call(PlayerDefeated, [=](EventListener *l) { l->onPlayerDefeated(player); });
}

void EventManager::aiSignal(Player *player, int signalId)
{
    call(AiSignal, [=](EventListener *l) { l->onAiSignal(player, signalId); });
}

void EventManager::attributeChanged(Player *player, int attributeId, float newValue)
{
    call(AttributeChanged, [=](EventListener *l) { l->onAttributeChanged(player, attributeId, newValue); });
}

void EventManager::unitDiscovered(Player *player, Unit *unit)
{
    call(DiscoveredUnit, [=](EventListener *l) { l->onUnitDiscovered(player, unit); });
}

void EventManager::unitDisappeared(Player *player, Unit *unit)
{
    call(UnitDisappeared, [=](EventListener *l) { l->onUnitDisappeared(player, unit); });
}

void EventManager::playerResourceChanged(Player *player, const genie::ResourceType type, const float newValue)
{
    call(PlayerResourceChanged, [=](EventListener *l) { l->onPlayerResourceChanged(player, type, newValue); });
}
