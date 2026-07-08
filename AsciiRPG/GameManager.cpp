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

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

GameManager::GameManager()
{
    std::shared_ptr<IConstructionParameter> mapParam
        = std::make_shared<Map::ConstructionParameter>(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT);
    
    map = ObjectManager::GetInstance().CreateOne<Map>( mapParam);

    //if( !map->GetNoMonsterFloor(&startPos) )
    //{
    //    cout << "Error: Failed to find a walkable cell in the map." << endl;
    //    return;
    //}

    //createMonster

    Vector2Int monsterPos(7, 7);
    shared_ptr<Entity> monsterEntity = CreationUtil::CreateMonster(monsterPos);

    map->AddEntityToCell(monsterPos.x, monsterPos.y, monsterEntity);

    //createPlayer
    Vector2Int playerPos(4, 4);
    auto playerEntity = CreationUtil::CreatePlayer(playerPos);

    map->AddEntityToCell(playerPos.x, playerPos.y, playerEntity);
}

void GameManager::Update()
{
    auto entities = ObjectManager::GetInstance().GetObjectsByType<Entity>();
    for (auto& entity : entities)
    {
        entity->Update();
    }
}