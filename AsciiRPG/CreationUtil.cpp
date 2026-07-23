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
#include "Dragon.h"
#include "DragonBullet.h"
#include "MonsterTable.h"
#include "IItem.h"
#include "NormalMonster.h"

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
        { StatType::Defense, Const::Stat::Player::INIT_DEFENSE },
        { StatType::Exp, 0 },
    }));
    playerStat->SetName(format("{}'s Stat", newPlayerEntity->GetName()));

    auto playerComponent = newPlayerEntity->AddComponent<Player>( std::make_shared<Component::ConstructionParamterBase>(newPlayerEntity));
    playerComponent->SetName(format("{}'s Player", newPlayerEntity->GetName()));

    return newPlayerEntity;
    
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

    auto wallDungeonObjectTag = newWallEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newWallEntity, DungeonTagTypes::Wall));
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

    auto entranceDungeonObjectTag = newEntranceEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newEntranceEntity, DungeonTagTypes::Entrance));

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

    auto exitDungeonObjectTag = newExitEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newExitEntity, DungeonTagTypes::Exit));
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

    auto floorDungeonObjectTag = newFloorEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newFloorEntity, DungeonTagTypes::None));
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

shared_ptr<Entity> CreationUtil::CreateFieldItem(Vector2Int position, shared_ptr<IItem> item, int quantity)
{
    auto newItemEntity = ObjectManager::GetInstance().CreateEntity();
    newItemEntity->SetName(format("FieldItem {0} {1}", position.x, position.y));

    auto itemPosition = newItemEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, newItemEntity));
    itemPosition->SetName(format("{}'s Position", newItemEntity->GetName()));

    auto itemRenderer = newItemEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::ITEM, newItemEntity));
    itemRenderer->SetName(format("{}'s Renderer", newItemEntity->GetName()));

    auto itemComponent = newItemEntity->AddComponent<FieldItem>(std::make_shared<FieldItem::ConstructionParameter>(newItemEntity, item->key, item->itemType, quantity));
    itemComponent->SetName(format("{}'s FieldItem", newItemEntity->GetName()));

    auto itemDungeonObjectTag = newItemEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(newItemEntity, DungeonTagTypes::FieldDropItem));

    itemDungeonObjectTag->SetName(format("{}'s DungeonObjectTag", newItemEntity->GetName()));

    return newItemEntity;
}

shared_ptr<Entity> CreationUtil::CreateNpc(Vector2Int position)
{
    auto npcEntity = ObjectManager::GetInstance().CreateEntity();

    npcEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, npcEntity));
    npcEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::NPC, npcEntity));
    npcEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(npcEntity, DungeonTagTypes::Alchemist));
    npcEntity->AddComponent<AlchemyShop>(std::make_shared<InteractableObject::ConstructionParameter>(npcEntity, InteractableObjectTags::AlchemyShop));

    return npcEntity;
}

shared_ptr<Entity> CreationUtil::CreateMonsterBase(Vector2Int position, char displayChar)
{
    auto monsterData = MonsterTable::GetInstance().GetMonsterData(displayChar);
    auto monsterEntity = ObjectManager::GetInstance().CreateEntity();
    monsterEntity->SetName(monsterData->name);

    monsterEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, monsterEntity));
    monsterEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(displayChar, monsterEntity));

    auto tagType = EnumUtility::ToDungeonTagTypes(displayChar);
    monsterEntity->AddComponent<DungeonObjectTag>(std::make_shared<DungeonObjectTag::ConstructionParameter>(monsterEntity, tagType));
    monsterEntity->AddComponent<Stat>(std::make_shared<Stat::ConstructionParameter>(monsterEntity
        , unordered_map<StatType, float>
            {
                { StatType::MaxHealth, monsterData->hp },
                { StatType::CurrentHealth, monsterData->hp },
                { StatType::Attack, monsterData->attack },
                { StatType::Defense, monsterData->defense },
                { StatType::AttackDelay, monsterData->attackDelay },
                { StatType::Exp, monsterData->exp },
            }));

    return monsterEntity;
}

shared_ptr<Entity> CreationUtil::CreateNormalMonster(Vector2Int position, char displayChar)  
{
    auto monsterData = MonsterTable::GetInstance().GetMonsterData(displayChar);
    auto monsterEntity = CreateMonsterBase(position, displayChar);

    shared_ptr<Monster::MonsterConstructionParameter> monsterConstructionParameter
        = std::make_shared<Monster::MonsterConstructionParameter>(monsterEntity, (int)monsterData->dropTableKey);

    monsterEntity->AddComponent<NormalMonster>(monsterConstructionParameter);
    return monsterEntity;
}

shared_ptr<Entity> CreationUtil::CreateDragon(Vector2Int position)
{
    auto dragonData = MonsterTable::GetInstance().GetMonsterData(Const::Map::DRAGON);
    auto dragonEntity = CreateMonsterBase(position, Const::Map::DRAGON);
    
    auto dragonComponent = dragonEntity->AddComponent<Dragon>(std::make_shared<Component::ConstructionParamterBase>(dragonEntity));
    dragonComponent->SetName(format("{}'s Dragon", dragonEntity->GetName()));

    return dragonEntity;
}

shared_ptr<Entity> CreationUtil::CreateDragonBullet(Vector2Int position, Vector2Int targetPosition, int damage)
{
    auto bulletEntity = ObjectManager::GetInstance().CreateEntity();
    auto bulletPosition = bulletEntity->AddComponent<Position>(std::make_shared<Position::ConstructParameter>(position.x, position.y, bulletEntity));
    auto bulletRenderer = bulletEntity->AddComponent<Renderer>(std::make_shared<Renderer::ConstructionParameter>(Const::Map::DRAGON_BULLET, bulletEntity));
    auto bulletComponent = bulletEntity->AddComponent<DragonBullet>(std::make_shared<DragonBullet::ConstructionParameter>(bulletEntity, position, targetPosition, Const::Stat::DRAGON_BULLET::SPEED, damage));

    return bulletEntity;
}

shared_ptr<Map> CreationUtil::CreateDragonRoom()
{
    vector<string> bossRoomString;

    bossRoomString.emplace_back("########################################");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#    S                                 #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                   D                  #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("#                                      #");
    bossRoomString.emplace_back("########################################");
    
    shared_ptr<Map> bossRoomMap = make_shared<Map>(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT);
    bossRoomMap->From(bossRoomString);
    return bossRoomMap;
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