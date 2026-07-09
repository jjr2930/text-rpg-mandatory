#include "Entrance.h"
#include "ObjectManager.h"
#include "Player.h"
#include "MathUtility.h"
#include "Position.h"
#include "Entity.h"
#include "Logger.h"

Entrance::Entrance(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    myPosition = entity->GetComponent<Position>();
}

void Entrance::Update()
{
    /*
    * 매우 비효율 적이군
    */
   auto components = ObjectManager::GetInstance().GetComponentsWithTypes<Player, Position>();
   //i need only one

   auto [player, playerPosition] = components[0];
   if(MathUtility::IsOverlap(myPosition->GetPosition(), playerPosition->GetPosition(), 0))
   {
       Logger::LogInfo("Player has entered the entrance!");
   }
}
