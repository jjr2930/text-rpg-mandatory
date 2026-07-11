#include "Wall.h"
#include "EventParameter.h"
#include "ObjectManager.h"

void Wall::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnMapClearRequested:
            ObjectManager::GetInstance().DestroyEntity(this->entity);
            break;

        default:
            break;
    }
}