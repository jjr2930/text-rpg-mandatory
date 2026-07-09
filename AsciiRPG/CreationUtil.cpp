#include "CreationUtil.h"
#include "ObjectManager.h"
#include "Entity.h"
#include "Position.h"
#include "Renderer.h"
#include "InputController.h"
#include "Wall.h"
#include "Entrance.h"
#include "Exit.h"
#include "Floor.h"
#include "Monster.h"
#include "Player.h"
#include "VirtualDisplay.h"

#include <string>
#include <format>

using namespace std;

/*
* TODO:와 인터페이스가 너무 똥인데?
*/

shared_ptr<Entity> CreationUtil::CreatePlayer(Vector2Int position)
{
    auto newPlayerEntity = ObjectManager::GetInstance().CreateEntity();
    newPlayerEntity->SetName(format("Player {0} {1}", position.x, position.y));
    newPlayerEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newPlayerEntity));
    newPlayerEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('P', newPlayerEntity));
    newPlayerEntity->AddComponent<InputController>(std::make_shared<Component::ConstructionParamterBase>(newPlayerEntity));
    newPlayerEntity->AddComponent<Player>(std::make_shared<Player::PlayerConstructionParameter>(newPlayerEntity, 100, 10, 5));

    return newPlayerEntity;
    
}

shared_ptr<Entity> CreationUtil::CreateMonster(Vector2Int position)
{
    auto newMonsterEntity = ObjectManager::GetInstance().CreateEntity();
    newMonsterEntity->SetName(format("Monster {0} {1}", position.x, position.y));
    newMonsterEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newMonsterEntity));
    newMonsterEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('M', newMonsterEntity));
    newMonsterEntity->AddComponent<Monster>(std::make_shared<Monster::MonsterConstructionParameter>(newMonsterEntity, 10, 5, 2, 10, 1, vector<DropItemData> {
        { "Gold", 10}, 
        { "Potion", 1 }
    }));

    return newMonsterEntity;
}

shared_ptr<Entity> CreationUtil::CreateWall(Vector2Int position)
{
    auto newWallEntity = ObjectManager::GetInstance().CreateEntity();
    newWallEntity->SetName(format("Wall {0} {1}", position.x, position.y));
        
    newWallEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newWallEntity));
    newWallEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('#', newWallEntity));
    newWallEntity->AddComponent<Wall>(std::make_shared<Component::ConstructionParamterBase>(newWallEntity));

    return newWallEntity; 
}

shared_ptr<Entity> CreationUtil::CreateEntrance(Vector2Int position)
{
    auto newEntranceEntity = ObjectManager::GetInstance().CreateEntity();
    newEntranceEntity->SetName(format("Entrance {0} {1}", position.x, position.y));

    newEntranceEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newEntranceEntity));
    newEntranceEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('E', newEntranceEntity));
    newEntranceEntity->AddComponent<Entrance>(std::make_shared<Component::ConstructionParamterBase>(newEntranceEntity));

    return newEntranceEntity; 
}

shared_ptr<Entity> CreationUtil::CreateExit(Vector2Int position)
{
    auto newExitEntity = ObjectManager::GetInstance().CreateEntity();
    newExitEntity->SetName(format("Exit {0} {1}", position.x, position.y));

    newExitEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newExitEntity));
    newExitEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('X', newExitEntity));
    newExitEntity->AddComponent<Exit>(std::make_shared<Component::ConstructionParamterBase>(newExitEntity));

    return newExitEntity;
}

shared_ptr<Entity> CreationUtil::CreateFloor(Vector2Int position)
{
    auto newFloorEntity = ObjectManager::GetInstance().CreateEntity();
    newFloorEntity->SetName(format("Floor {0} {1}", position.x, position.y));

    newFloorEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newFloorEntity));
    newFloorEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(' ', newFloorEntity));
    newFloorEntity->AddComponent<Floor>(std::make_shared<Component::ConstructionParamterBase>(newFloorEntity));

    return newFloorEntity;
}

shared_ptr<Entity> CreationUtil::CreateVirtualDisplay()
{
    auto newVirtualDisplayEntity = ObjectManager::GetInstance().CreateEntity();
    newVirtualDisplayEntity->SetName("VirtualDisplay");
    newVirtualDisplayEntity->AddComponent<VirtualDisplay>(std::make_shared<Component::ConstructionParamterBase>(newVirtualDisplayEntity));

    return newVirtualDisplayEntity;
}
