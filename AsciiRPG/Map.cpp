#include "Map.h"
#include "Random.h"
#include "Const.h"
#include "Entity.h"
#include "ObjectManager.h"
#include "CreationUtil.h"
#include "DungeonObjectTag.h"
#include "Position.h"
#include "Logger.h"

#include <format>
#include <random>
#include <iostream>
#include <cassert>

using namespace std;

//
//Map::Map(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
//    : Object(id, name, params)
//{
//    auto mapParam = static_cast<ConstructionParameter*>(params.get());
//    if (mapParam)
//    {
//        width = mapParam->width;
//        height = mapParam->height;
//    }
//
//    for (int i = 0; i < width * height; ++i)
//    {
//        int x = i % width;
//        int y = i / width;
//        
//        MapCell* newCell = new MapCell(x, y);  
//        cells.push_back(newCell);
//        
//        if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
//        {
//            //auto newFloor = CreationUtil::CreateFloor(newCell->GetPosition());
//            //newCell->AddEntity(newFloor);
//        }
//        else
//        {
//            auto newWall = CreationUtil::CreateWall(newCell->GetPosition());
//            newCell->AddEntity(newWall);
//        }
//    }
//
//    Vector2Int entrancePos(3, 3);
//    Vector2Int exitPos(width - 4, height - 4);
//
//    auto newEntrance = CreationUtil::CreateEntrance(entrancePos);
//    auto newExit = CreationUtil::CreateExit(exitPos);
//
//    AddEntityToCell(entrancePos.x, entrancePos.y, newEntrance);
//    AddEntityToCell(exitPos.x, exitPos.y, newExit);
//
//    entranceCellIndex = entrancePos;
//    exitCellIndex = exitPos;
//}

Map::Map(int width, int height)
    : rawData(new char[height * width])
    , size(width, height)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width + x;
            rawData[index] = Const::Map::EMPTY;
        }
    }
}

Map::~Map()
{
    delete[] rawData;
}
void Map::SetCellData(int x, int y, char data)
{
    assert(x >= 0 && x < size.x && y >= 0 && y < size.y);
    int index = y * size.x + x;
    rawData[index] = data;
}

char Map::GetCellData(int x, int y) const
{
    assert(x >= 0 && x < size.x && y >= 0 && y < size.y);
    int index = y * size.x + x;
    return rawData[index];
}

//현재 출력되고 있는 맵 데이터를 수집하는 함수. 
void Map::CollectMapData()
{
    Clear();

    auto pairs = ObjectManager::GetInstance().GetComponentsWithTypes<DungeonObjectTag, Position>();
    for (auto& [tag, position] : pairs)
    {
        Vector2Int pos = position->GetPosition();
        int index = pos.y * size.x + pos.x;
        char tagChar = tag->GetTag();
        rawData[index] = tagChar;

        //Logger::LogInfo(format("Collecting Map Data: Position ({}, {}), Tag '{}'", pos.x, pos.y, tagChar));
    }
}
void Map::Clear()
{
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            int index = y * size.x + x;
            rawData[index] = Const::Map::EMPTY;
        }
    }
}
void Map::From(const vector<string>& source)
{
    assert(source.size() <= size.y && "Source map height exceeds Map size.");

    size_t lineSize = source.size();
    for (size_t i = 0; i < lineSize; ++i)
    {
        const string& line = source[i];
        assert(line.size() <= size.x && "Source map width exceeds Map size.");
        for (size_t j = 0; j < line.size(); ++j)
        {
            SetCellData(static_cast<int>(j), static_cast<int>(i), line[j]);
        }
    }
}
//
//void Map::AddEntityToCell(int x, int y, shared_ptr<Entity> entity)
//{
//    MapCell* cell = GetCell(x, y);
//    if (cell)
//    {
//        cell->AddEntity(entity);
//    }
//}
//
//void Map::RemoveEntityFromCell(int x, int y, shared_ptr<Entity> entity)
//{
//    MapCell* cell = GetCell(x, y);
//    if (cell)
//    {
//        cell->RemoveEntity(entity);
//    }
//}
//
//Vector2Int Map::GetEntranceCellIndex() const
//{
//    return entranceCellIndex;
//}
//
//Vector2Int Map::GetExitCellIndex() const
//{
//    return exitCellIndex;
//}
//
//MapCell* Map::GetCell(int x, int y)
//{
//    if (x < 0 || x >= width || y < 0 || y >= height)
//        return nullptr;
//
//    int index = y * width + x;
//
//    return cells[index];
//}
//
//MapCell* Map::GetRandomCellWithoutBound()
//{
//    int randomX = Random::GetInstance().RandomRange(1, width - 2);
//    int randomY = Random::GetInstance().RandomRange(1, height - 2);
//    int randomIndex = randomY * width + randomX;
//
//    return cells[randomIndex];
//}
//
//MapCell* Map::GetRandomCell(int minX, int maxX, int minY, int maxY)
//{
//    int randomX = Random::GetInstance().RandomRange(minX, maxX);
//    int randomY = Random::GetInstance().RandomRange(minY, maxY);
//    int randomIndex = randomY * width + randomX;
//
//    return cells[randomIndex];
//}
//
//MapCell* Map::GetNeighbourCell(int x, int y, Dicrection dir)
//{
//    int targetX = x;
//    int targetY = y;
//
//    switch (dir)
//    {
//    case Dicrection::Up: targetY--; break;
//    case Dicrection::Down: targetY++; break;
//    case Dicrection::Left: targetX--; break;
//    case Dicrection::Right: targetX++; break;
//    default:
//        return nullptr;
//    }
//
//    // 테두리냐
//    if (targetX == 0 || targetX == width - 1)
//        return nullptr;
//
//    if (targetY == 0 || targetY == height - 1)
//        return nullptr;
//   
//    else
//        return GetCell(targetX, targetY);
//}
//
//MapCell* Map::GetRandomNeighbourCell(MapCell* cell)
//{
//    auto neighbours = GetNeighbours(cell);
//    if (neighbours.empty())
//    {
//        return nullptr;
//    }
//
//    int randomIndex = Random::GetInstance().RandomRange(0, neighbours.size() - 1);
//    return neighbours[randomIndex];
//}
//
//std::vector<MapCell*> Map::GetNeighbours(int x, int y)
//{
//    std::vector<MapCell*> neighbours;
//    neighbours.reserve((int)Dicrection::Count);
//
//    for (int i = 0; i < (int)Dicrection::Count; ++i)
//    {
//        MapCell* neighbour = GetNeighbourCell(x, y, static_cast<Dicrection>(i));
//        if (nullptr != neighbour)
//        {
//            neighbours.emplace_back(neighbour);
//        }
//    }
//
//    return neighbours;
//}
//
//std::vector<MapCell*> Map::GetNeighbours(Vector2Int position)
//{
//    return GetNeighbours(position.x, position.y);
//}
//
//std::vector<MapCell*> Map::GetNeighbours(MapCell* cell)
//{
//    return GetNeighbours(cell->GetX(), cell->GetY());
//}
