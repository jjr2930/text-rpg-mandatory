#include "NPC.h"
#include "Entity.h"
#include "Position.h"
#include "MathUtility.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Logger.h"

#include <cassert>
#include <format>

using namespace std;

Npc::Npc(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    if (auto entityPtr = entity.lock())
    {
        npcPosition = entityPtr->GetComponent<Position>();
    }
}

void Npc::Update()
{
    assert(npcPosition != nullptr && "Npc position is null");

    auto [player, position] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
    
    if(MathUtility::IsOverlap(npcPosition->GetPosition(), position->GetPosition(), 1))
    {
        if (lastOverlapEntityId != player->GetId())
        {
            Logger::LogInfo("Stay awhile and listen!");

            lastOverlapEntityId = player->GetId();
        }
    }
    else
    {
        lastOverlapEntityId = -1;
    }
}
