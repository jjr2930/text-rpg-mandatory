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
#include "DungeonObjectTag.h"
#include "Const.h"
#include "Stat.h"
#include "Map.h"
#include "Npc.h"
#include "InteractableObject.h"
#include "Enums.h"
#include "AlchemyShop.h"

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

    auto playerRenderer = newPlayerEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::PLAYER, newPlayerEntity));
    playerRenderer->SetName(format("{}'s Renderer", newPlayerEntity->GetName()));

    auto playerInputController = newPlayerEntity->AddComponent<InputController>(std::make_shared<Component::ConstructionParamterBase>(newPlayerEntity));
    playerInputController->SetName(format("{}'s InputController", newPlayerEntity->GetName()));
    
    auto playerStat = newPlayerEntity->AddComponent<Stat>(std::make_shared<Stat::ConstructionParameter>(newPlayerEntity, unordered_map<StatType, float>{
        { StatType::MaxHealth, Const::Stat::Player::INIT_HP },
        { StatType::CurrentHealth, Const::Stat::Player::INIT_HP },
        { StatType::Attack, Const::Stat::Player::INIT_ATTACK },
        { StatType::Defense, Const::Stat::Player::INIT_DEFENSE }
    }));
    playerStat->SetName(format("{}'s Stat", newPlayerEntity->GetName()));

    auto playerComponent = newPlayerEntity->AddComponent<Player>( std::make_shared<Component::ConstructionParamterBase>(newPlayerEntity));
    playerComponent->SetName(format("{}'s Player", newPlayerEntity->GetName()));

    return newPlayerEntity;
    
}

shared_ptr<Entity> CreationUtil::CreateMonster(Vector2Int position)
{
    auto newMonsterEntity = ObjectManager::GetInstance().CreateEntity();
    newMonsterEntity->SetName(format("Monster {0} {1}", position.x, position.y));

    auto monsterPosition = newMonsterEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newMonsterEntity));
    monsterPosition->SetName(format("{}'s Position", newMonsterEntity->GetName()));

    auto monsterRenderer = newMonsterEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::MONSTER, newMonsterEntity));
    monsterRenderer->SetName(format("{}'s Renderer", newMonsterEntity->GetName()));

    auto monsterComponent = newMonsterEntity->AddComponent<Monster>(std::make_shared<Monster::MonsterConstructionParameter>(newMonsterEntity, 10, 10, 2, 10, 1, vector<DropItemData> {
        { 1, 10}, 
        { 2, 1 }
    }));
    monsterComponent->SetName(format("{}'s Monster", newMonsterEntity->GetName()));
    
    auto monsterDungeonObjectTag = newMonsterEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newMonsterEntity, Const::Map::MONSTER));
    monsterDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newMonsterEntity->GetName()));


    auto monsterStat = newMonsterEntity->AddComponent<Stat>(std::make_shared<Stat::ConstructionParameter>(newMonsterEntity, unordered_map<StatType, float>{
        { StatType::MaxHealth, 10.0f },
        { StatType::CurrentHealth, 10.0f },
        { StatType::Attack, 10.0f },
        { StatType::Defense, 2.0f }
    }));
    return newMonsterEntity;
}

shared_ptr<Entity> CreationUtil::CreateWall(Vector2Int position)
{
    auto newWallEntity = ObjectManager::GetInstance().CreateEntity();
    newWallEntity->SetName(format("Wall {0} {1}", position.x, position.y));
        
    auto wallPosition = newWallEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newWallEntity));
    wallPosition->SetName(format("{}'s Position", newWallEntity->GetName()));
    
    auto wallRenderer = newWallEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::WALL, newWallEntity));
    wallRenderer->SetName(format("{}'s Renderer", newWallEntity->GetName()));
    
    auto wallComponent = newWallEntity->AddComponent<Wall>(std::make_shared<Component::ConstructionParamterBase>(newWallEntity));
    wallComponent->SetName(format("{}'s Wall", newWallEntity->GetName()));

    auto wallDungeonObjectTag = newWallEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newWallEntity, Const::Map::WALL));
    wallDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newWallEntity->GetName()));

    return newWallEntity; 
}

shared_ptr<Entity> CreationUtil::CreateEntrance(Vector2Int position)
{
    auto newEntranceEntity = ObjectManager::GetInstance().CreateEntity();
    newEntranceEntity->SetName(format("Entrance {0} {1}", position.x, position.y));

    auto entrancePosition = newEntranceEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newEntranceEntity));
    entrancePosition->SetName(format("{}'s Position", newEntranceEntity->GetName()));

    auto entranceRenderer = newEntranceEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::START, newEntranceEntity));
    entranceRenderer->SetName(format("{}'s Renderer", newEntranceEntity->GetName()));

    auto entranceComponent = newEntranceEntity->AddComponent<Entrance>(std::make_shared<Component::ConstructionParamterBase>(newEntranceEntity));
    entranceComponent->SetName(format("{}'s Entrance", newEntranceEntity->GetName()));

    auto entranceDungeonObjectTag = newEntranceEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newEntranceEntity, Const::Map::START));

    entranceDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newEntranceEntity->GetName()));   

    return newEntranceEntity; 
}

shared_ptr<Entity> CreationUtil::CreateExit(Vector2Int position)
{
    auto newExitEntity = ObjectManager::GetInstance().CreateEntity();
    newExitEntity->SetName(format("Exit {0} {1}", position.x, position.y));

    auto exitPosition = newExitEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newExitEntity));
    exitPosition->SetName(format("{}'s Position", newExitEntity->GetName()));
    auto exitRenderer = newExitEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::EXIT, newExitEntity));
    exitRenderer->SetName(format("{}'s Renderer", newExitEntity->GetName()));
    auto exitComponent = newExitEntity->AddComponent<Exit>(std::make_shared<Component::ConstructionParamterBase>(newExitEntity));
    exitComponent->SetName(format("{}'s Exit", newExitEntity->GetName()));

    auto exitDungeonObjectTag = newExitEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newExitEntity, Const::Map::EXIT));
    exitDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newExitEntity->GetName()));

    return newExitEntity;
}

shared_ptr<Entity> CreationUtil::CreateFloor(Vector2Int position)
{
    auto newFloorEntity = ObjectManager::GetInstance().CreateEntity();
    newFloorEntity->SetName(format("Floor {0} {1}", position.x, position.y));

    auto floorPosition = newFloorEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newFloorEntity));
    floorPosition->SetName(format("{}'s Position", newFloorEntity->GetName()));

    auto floorRenderer = newFloorEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::EMPTY, newFloorEntity));
    floorRenderer->SetName(format("{}'s Renderer", newFloorEntity->GetName()));

    auto floorComponent = newFloorEntity->AddComponent<Floor>(std::make_shared<Component::ConstructionParamterBase>(newFloorEntity));
    floorComponent->SetName(format("{}'s Floor", newFloorEntity->GetName()));

    auto floorDungeonObjectTag = newFloorEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newFloorEntity, Const::Map::EMPTY));
    floorDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newFloorEntity->GetName()));

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

shared_ptr<Entity> CreationUtil::CreateFieldItem(Vector2Int position, int itemKey, int quantity)
{
    auto newItemEntity = ObjectManager::GetInstance().CreateEntity();
    newItemEntity->SetName(format("FieldItem {0} {1}", position.x, position.y));

    auto itemPosition = newItemEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newItemEntity));
    itemPosition->SetName(format("{}'s Position", newItemEntity->GetName()));

    auto itemRenderer = newItemEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::ITEM, newItemEntity));
    itemRenderer->SetName(format("{}'s Renderer", newItemEntity->GetName()));

    auto itemComponent = newItemEntity->AddComponent<FieldItem>(std::make_shared<FieldItem::ConstructionParameter>(newItemEntity, itemKey, quantity));
    itemComponent->SetName(format("{}'s FieldItem", newItemEntity->GetName()));

    auto itemDungeonObjectTag = newItemEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newItemEntity, Const::Map::ITEM));
    itemDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newItemEntity->GetName()));

    return newItemEntity;
}

shared_ptr<Entity> CreationUtil::CreateNpc(Vector2Int position)
{
    auto npcEntity = ObjectManager::GetInstance().CreateEntity();

    npcEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, npcEntity));
    npcEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::NPC, npcEntity));
    npcEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(npcEntity, Const::Map::NPC));
    npcEntity->AddComponent<AlchemyShop>(std::make_shared<InteractableObject::ConstructionParameter>(npcEntity, InteractableObjectTags::AlchemyShop));

    return npcEntity;
}

shared_ptr<Map> CreationUtil::CreateTownMap()
{
    //clear
    vector<string> townMapString;
    //A alchemy shop
    //F forge

    townMapString.emplace_back("########################################");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#      ###########################     #");
    townMapString.emplace_back("#      #         N               #     #");
    townMapString.emplace_back("#      #                         #     #");
    townMapString.emplace_back("#      #           S    X        #     #");
    townMapString.emplace_back("#      #                         #     #");
    townMapString.emplace_back("#      #                         #     #");
    townMapString.emplace_back("#      ###########################     #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("#                                      #");
    townMapString.emplace_back("########################################");
    
    shared_ptr<Map> townMap = make_shared<Map>(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT);
    townMap->From(townMapString);
    return townMap;
}