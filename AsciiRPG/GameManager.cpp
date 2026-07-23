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
#include "Logger.h"
#include "GameTime.h"
#include "MonsterTable.h"
#include "ItemBank.h"

#include <memory>
#include <vector>
#include <iostream>
#include <format>

using namespace std;

GameManager::GameManager()
    : currentMapIndex(0)
{

    CreationUtil::CreatePlayer(Vector2Int(3, 3));

    //1 is town map
    maps.reserve(Const::Map::DUNGEON_DEPTH + 1);

    shared_ptr<Map> townMap = CreationUtil::CreateTownMap();
    maps.emplace_back(townMap);

    RandomMapGenerator rmg;

    for (int i = 1; i < Const::Map::DUNGEON_DEPTH + 1; ++i)
    {
        shared_ptr<Map> newMap = make_shared<Map>(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT);

        rmg.GenerateRandomMap(Const::Map::DEFAULT_WIDTH, Const::Map::DEFAULT_HEIGHT, i, newMap);

        maps.emplace_back(newMap);
    }

    shared_ptr<Map> dragonRoom = CreationUtil::CreateDragonRoom();
    maps.emplace_back(dragonRoom);

    currentMapIndex = 0;
    CreateCurrentMapObjects(true);

    auto virtualDisplayEntity = CreationUtil::CreateVirtualDisplay();
    virtualDisplay = virtualDisplayEntity->GetComponent<VirtualDisplay>();
}

void GameManager::Update()
{
    GameTime::CalculateDeltaTime();

    auto entities = ObjectManager::GetInstance().GetAllEntities();
    for (auto& entity : *entities)
    {
            //TODO: 음?? Entity가 없는 경우가 있을 수 있는데 왜 동작하지?
        entity->Update();
        //ObjectManager::GetInstance().PrintCurrentState();
    }

    //TODO: 약간 억지 같음
    virtualDisplay->Render();
}

void GameManager::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnPlayerEnteredExit:
            ChangeMap(currentMapIndex + 1);
            break;


        case EventType::OnPlayerEnteredEntrance:
            ChangeMap(currentMapIndex - 1);
            break;
        default:
            break;
    }
}

void GameManager::CreateCurrentMapObjects(bool goingToDown)
{
    for(int y = 0; y < Const::Map::DEFAULT_HEIGHT; ++y)
    {
        for(int x = 0; x < Const::Map::DEFAULT_WIDTH; ++x)
        {
            DungeonTagTypes cellType = maps[currentMapIndex]->GetCellData(x, y);
            char cellChar = EnumUtility::ToChar(cellType);
            switch (cellChar)
            {
                case Const::Map::WALL:
                    CreationUtil::CreateWall(Vector2Int(x, y));
                    break;

                case Const::Map::START:
                    {
                        CreationUtil::CreateEntrance(Vector2Int(x, y));
                        if (goingToDown)
                        {
                            auto [player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
                            playerPosition->SetPosition(x, y);
                            //Logger::LogInfo(format("Entrance Position : ({}, {}), Player position set to ({}, {})", x, y, x, y));
                        }
                    }
                    break;

                case Const::Map::EXIT:
                    {
                        CreationUtil::CreateExit(Vector2Int(x, y));
                        if (!goingToDown)
                        {
                            auto [player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
                            playerPosition->SetPosition(x, y);
                            //Logger::LogInfo(format("Exit Position : ({}, {}), Player position set to ({}, {})", x, y, x, y));
                        }
                    }
                    break;

                case Const::Map::ITEM:
                    {
                        shared_ptr<IItem> randomItem = ItemBank::GetInstance().GetRandomItem();
                        int quantity = Random::GetInstance().RandomRange(1, 10);
                        CreationUtil::CreateFieldItem(Vector2Int(x, y), randomItem, quantity);
                    }
                    break;

                case Const::Map::NPC:
                    CreationUtil::CreateNpc(Vector2Int(x, y));
                    break;

                case Const::Map::DRAGON:
                    CreationUtil::CreateDragon(Vector2Int(x, y));
                    break;

                default:
                    if (MonsterTable::GetInstance().IsExist(cellChar))
                    {
                        CreationUtil::CreateMonster(Vector2Int(x, y), cellChar);
                    }   
                    break;
            }
        }
    }}

void GameManager::ChangeMap(int newMapIndex)
{
    int mapSize = maps.size();

    if (newMapIndex >= mapSize)
    {
        Logger::LogInfo("Player has reached the final exit. Game Over!");
        return;
    }

    if (newMapIndex < 0)
    {
        Logger::LogInfo("Player has reached the first entrance!!");
        return;
    }

    Logger::LogInfo(format("Collect current map data, index: {}", currentMapIndex));
    maps[currentMapIndex]->CollectMapData();

    ObjectManager::GetInstance().BroadcastEvent(make_shared<EventParameter>(EventType::OnMapClearRequested));

    //ObjectManager::GetInstance().PrintCurrentState();

    int oldIndex = currentMapIndex;
    currentMapIndex = newMapIndex;
    CreateCurrentMapObjects(oldIndex < newMapIndex);

    Logger::LogInfo(format("change map, index: {}", currentMapIndex));
}
