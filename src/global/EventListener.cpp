#include "EventListener.h"
#include "EventManager.h"

EventListener::EventListener()
{

}

EventListener::~EventListener()
{
    EventManager::onListenerDestroyed(this);
}
