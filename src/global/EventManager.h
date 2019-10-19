#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <array>
#include <functional>
#include <list>

struct EventListener;
struct MapPos;
struct Player;
struct Unit;

namespace genie {
enum class ResourceType : int16_t;
}

// Not scalable at all, so sue me
class EventManager
{
public:
    // Conditions used in tutorial scenario (that should be implemented first):
    //  - OwnObjects (3)
    //  - OwnFewerObjects (4)
    //  - ObjectsInArea (5)
    //  - DestroyObject (6)
    //  - Timer (10)
    //  - ObjectSelected (11)

    enum EventType {
        UnitCreated,
        UnitDestroyed,
        UnitSelected,
        UnitDeselected,
        UnitChangedOwner,
        UnitCaptured,
        UnitMoved,
        UnitGarrisoned,
        UnitGotTarget,
        UnitDeliveredUnit,

        ResearchStarted,
        ResearchComplete,
        PlayerDefeated,
        AiSignal,
        AttributeChanged,
        DiscoveredUnit,
        UnitDisappeared,

        PlayerResourceChanged,

        EventTypeCount
    };

    static void registerListener(EventListener *listener, const EventType type);
    static void deregisterListener(EventListener *listener);
    static void deregisterListener(EventListener *listener, const EventType type);
    static void onListenerDestroyed(EventListener *listener);

    static void unitCreated(Unit *unit);
    static void unitDying(Unit *unit);
    static void unitSelected(Unit *unit);
    static void unitDeselected(const Unit *unit);
    static void unitOwnerChanged(Unit *unit, int oldPlayerId, int newPlayerId);
    static void unitCaptured(Unit *unit, int oldPlayerId, int newPlayerId);
    static void unitMoved(Unit *unit, const MapPos &oldtile, const MapPos &newTile);
    static void unitGarrisoned(Unit *unit, Unit *garrisonedIn);
    static void unitGotTarget(Unit *unit, Unit *targetUnit);
    static void unitDelivered(Unit *unit, Unit *deliveredUnit, Unit *targetUnit);

    static void researchStarted(Player *player, int researchId);
    static void researchCompleted(Player *player, int researchId);
    static void playerDefeated(Player *player);
    static void aiSignal(Player *player, int signalId);
    static void attributeChanged(Player *player, int attributeId, float newValue);
    static void unitDiscovered(Player *player, Unit *unit);
    static void unitDisappeared(Player *player, Unit *unit);

    static void playerResourceChanged(Player *player, const genie::ResourceType type, const float newValue);

private:
    static void call(const EventType type, std::function<void(EventListener *listener)> function)
    {
        for (EventListener *listener : instance()->m_entityEventListeners[type]) {
            function(listener);
        }
    }

    EventManager();
    static EventManager *instance();

    std::array<std::list<EventListener*>, EventTypeCount> m_entityEventListeners;

};

#endif // EVENTMANAGER_H
