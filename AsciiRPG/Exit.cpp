#include "Exit.h"
#include "Entity.h"
#include "Position.h"
#include "ObjectManager.h"
#include "Player.h"
#include "MathUtility.h"
#include "Logger.h"
#include "EventParameter.h"

Exit::Exit(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    if (auto ptr = entity.lock())
    {
        myPosition = ptr->GetComponent<Position>();
    }
}

void Exit::Update()
{
    /*
    * 매우 비효율 적이군
    */
   auto components = ObjectManager::GetInstance().GetComponentsWithTypes<Player, Position>();
   //i need only one

   auto [player, playerPosition] = components[0];
   if(MathUtility::IsOverlap(myPosition->GetPosition(), playerPosition->GetPosition(), 0))
   {
       if (active)
       {
           ObjectManager::GetInstance().BroadcastEvent(make_shared<EventParameter>(EventType::OnPlayerEnteredExit));
           active = false;
       }
   }
   else
   {
       if(!active)
       {
           Logger::LogInfo("Player exited the Exit!");
           active = true;
       }
   }
}

void Exit::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnMapClearRequested:
            if (auto entityPtr = entity.lock())
            {
                ObjectManager::GetInstance().DestroyEntity(entityPtr);
            }   
            break;

        default:
            break;
    }
}
