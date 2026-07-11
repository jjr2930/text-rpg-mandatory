#include "Wall.h"
#include "EventParameter.h"
#include "ObjectManager.h"

void Wall::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnMapClearRequested:
            DestroyEntity();
            break;

        default:
            break;
    }
}