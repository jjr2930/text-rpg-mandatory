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
#include "FieldItem.h"

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
    
    auto playerPosition = newPlayerEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newPlayerEntity));
    playerPosition->SetName(format("{}'s Position", newPlayerEntity->GetName()));

    auto playerRenderer = newPlayerEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('P', newPlayerEntity));
    playerRenderer->SetName(format("{}'s Renderer", newPlayerEntity->GetName()));

    auto playerInputController = newPlayerEntity->AddComponent<InputController>(std::make_shared<Component::ConstructionParamterBase>(newPlayerEntity));
    playerInputController->SetName(format("{}'s InputController", newPlayerEntity->GetName()));

    auto playerComponent = newPlayerEntity->AddComponent<Player>(std::make_shared<Player::PlayerConstructionParameter>(newPlayerEntity, 100, 10, 5));
    playerComponent->SetName(format("{}'s Player", newPlayerEntity->GetName()));

    return newPlayerEntity;
    
}

shared_ptr<Entity> CreationUtil::CreateMonster(Vector2Int position)
{
    auto newMonsterEntity = ObjectManager::GetInstance().CreateEntity();
    newMonsterEntity->SetName(format("Monster {0} {1}", position.x, position.y));

    auto monsterPosition = newMonsterEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newMonsterEntity));
    monsterPosition->SetName(format("{}'s Position", newMonsterEntity->GetName()));

    auto monsterRenderer = newMonsterEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('M', newMonsterEntity));
    monsterRenderer->SetName(format("{}'s Renderer", newMonsterEntity->GetName()));

    auto monsterComponent = newMonsterEntity->AddComponent<Monster>(std::make_shared<Monster::MonsterConstructionParameter>(newMonsterEntity, 10, 5, 2, 10, 1, vector<DropItemData> {
        { "Gold", 10}, 
        { "Potion", 1 }
    }));
    monsterComponent->SetName(format("{}'s Monster", newMonsterEntity->GetName()));

    return newMonsterEntity;
}

shared_ptr<Entity> CreationUtil::CreateWall(Vector2Int position)
{
    auto newWallEntity = ObjectManager::GetInstance().CreateEntity();
    newWallEntity->SetName(format("Wall {0} {1}", position.x, position.y));
        
    auto wallPosition = newWallEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newWallEntity));
    wallPosition->SetName(format("{}'s Position", newWallEntity->GetName()));
    auto wallRenderer = newWallEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('#', newWallEntity));
    wallRenderer->SetName(format("{}'s Renderer", newWallEntity->GetName()));
    auto wallComponent = newWallEntity->AddComponent<Wall>(std::make_shared<Component::ConstructionParamterBase>(newWallEntity));
    wallComponent->SetName(format("{}'s Wall", newWallEntity->GetName()));

    return newWallEntity; 
}

shared_ptr<Entity> CreationUtil::CreateEntrance(Vector2Int position)
{
    auto newEntranceEntity = ObjectManager::GetInstance().CreateEntity();
    newEntranceEntity->SetName(format("Entrance {0} {1}", position.x, position.y));

    auto entrancePosition = newEntranceEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newEntranceEntity));
    entrancePosition->SetName(format("{}'s Position", newEntranceEntity->GetName()));
    auto entranceRenderer = newEntranceEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('E', newEntranceEntity));
    entranceRenderer->SetName(format("{}'s Renderer", newEntranceEntity->GetName()));
    auto entranceComponent = newEntranceEntity->AddComponent<Entrance>(std::make_shared<Component::ConstructionParamterBase>(newEntranceEntity));
    entranceComponent->SetName(format("{}'s Entrance", newEntranceEntity->GetName()));

    return newEntranceEntity; 
}

shared_ptr<Entity> CreationUtil::CreateExit(Vector2Int position)
{
    auto newExitEntity = ObjectManager::GetInstance().CreateEntity();
    newExitEntity->SetName(format("Exit {0} {1}", position.x, position.y));

    auto exitPosition = newExitEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newExitEntity));
    exitPosition->SetName(format("{}'s Position", newExitEntity->GetName()));
    auto exitRenderer = newExitEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('X', newExitEntity));
    exitRenderer->SetName(format("{}'s Renderer", newExitEntity->GetName()));
    auto exitComponent = newExitEntity->AddComponent<Exit>(std::make_shared<Component::ConstructionParamterBase>(newExitEntity));
    exitComponent->SetName(format("{}'s Exit", newExitEntity->GetName()));

    return newExitEntity;
}

shared_ptr<Entity> CreationUtil::CreateFloor(Vector2Int position)
{
    auto newFloorEntity = ObjectManager::GetInstance().CreateEntity();
    newFloorEntity->SetName(format("Floor {0} {1}", position.x, position.y));

    auto floorPosition = newFloorEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newFloorEntity));
    floorPosition->SetName(format("{}'s Position", newFloorEntity->GetName()));
    auto floorRenderer = newFloorEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(' ', newFloorEntity));
    floorRenderer->SetName(format("{}'s Renderer", newFloorEntity->GetName()));
    auto floorComponent = newFloorEntity->AddComponent<Floor>(std::make_shared<Component::ConstructionParamterBase>(newFloorEntity));
    floorComponent->SetName(format("{}'s Floor", newFloorEntity->GetName()));

    return newFloorEntity;
}

shared_ptr<Entity> CreationUtil::CreateVirtualDisplay()
{
    auto newVirtualDisplayEntity = ObjectManager::GetInstance().CreateEntity();
    newVirtualDisplayEntity->SetName("VirtualDisplay");
    auto virtualDisplayComponent = newVirtualDisplayEntity->AddComponent<VirtualDisplay>(std::make_shared<Component::ConstructionParamterBase>(newVirtualDisplayEntity));
    virtualDisplayComponent->SetName(format("{}'s VirtualDisplay", newVirtualDisplayEntity->GetName()));

    return newVirtualDisplayEntity;
}

shared_ptr<Entity> CreationUtil::CreateFieldItem(Vector2Int position, const string& itemName, int quantity)
{
    auto newItemEntity = ObjectManager::GetInstance().CreateEntity();
    newItemEntity->SetName(format("FieldItem {0} {1}", position.x, position.y));
    auto itemPosition = newItemEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newItemEntity));
    itemPosition->SetName(format("{}'s Position", newItemEntity->GetName()));
    auto itemRenderer = newItemEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>('*', newItemEntity));
    itemRenderer->SetName(format("{}'s Renderer", newItemEntity->GetName()));
    auto itemComponent = newItemEntity->AddComponent<FieldItem>(std::make_shared<FieldItem::ConstructionParameter>(newItemEntity, itemName, quantity));
    itemComponent->SetName(format("{}'s FieldItem", newItemEntity->GetName()));

    return newItemEntity;
}
