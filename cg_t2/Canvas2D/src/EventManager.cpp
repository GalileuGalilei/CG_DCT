#include "EventManager.h"
#include <type_traits>

EventType BaseEvent::GetStaticType()
{
	return EventType::None;
}

using EvenFunc = void(*)(BaseEvent*);
using EventList = std::list<EvenFunc>;
using EventMap = EventList[EventType::Count];

EventMap EventManager::eventMap;
EventManager* EventManager::instance = NULL;

EventManager* EventManager::Instance()
{
	if (instance == NULL)
	{
		instance = new EventManager();
	}

	return instance;
}