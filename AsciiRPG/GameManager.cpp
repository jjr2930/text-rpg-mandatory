#include "GameManager.h"
#include "Map.h"
#include "ObjectManager.h"
#include "Const.h"
#include "IConstructionParameter.h"
#include "Vector2Int.h"
#include "Entity.h"
#include "Position.h"
#include "Renderer.h"
#include "InputController.h"
#include "CreationUtil.h"
#include "VirtualDisplay.h"
#include "RandomMapGenerator.h"
#include "EventParameter.h"
#include "Player.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

GameManager::GameManager()
{
    RandomMapGenerator rmg;
    rmg.GenerateRandomMap(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT);

    auto virtualDisplayEntity = CreationUtil::CreateVirtualDisplay();
    virtualDisplay = virtualDisplayEntity->GetComponent<VirtualDisplay>();
}

void GameManager::Update()
{
    auto entities = ObjectManager::GetInstance().GetObjectsByType<Entity>();
    for (auto& entity : entities)
    {
        //TODO: 음?? Entity가 없는 경우가 있을 수 있는데 왜 동작하지?
        entity->Update();
    }

    //TODO: 약간 억지 같음
    virtualDisplay->Render();
}

void GameManager::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnPlayerEnteredExit:
            ObjectManager::GetInstance().BroadcastEvent(make_shared<EventParameter>(EventType::OnMapClearRequested));

            CreateNewMap();
            break;
        default:
            break;
    }
}

void GameManager::CreateNewMap()
{
    RandomMapGenerator rmg;

    shared_ptr<Player> player = ObjectManager::GetInstance().GetObjectByType<Player>();
    rmg.GenerateRandomMap(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT, player->GetEntity());
}
