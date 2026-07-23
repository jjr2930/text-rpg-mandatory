#include "Map.h"
#include "Random.h"
#include "Const.h"
#include "Entity.h"
#include "ObjectManager.h"
#include "CreationUtil.h"
#include "DungeonObjectTag.h"
#include "Position.h"
#include "Logger.h"
#include "Array2D.h"

#include <format>
#include <random>
#include <iostream>
#include <cassert>

using namespace std;

Map::Map(int width, int height)
    : data(width, height)
    , size(width, height)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            data(x, y) =  Const::Map::EMPTY;
        }
    }
}

void Map::SetCellData(int x, int y, DungeonTagTypes entityType)
{
    assert(x >= 0 && x < size.x && y >= 0 && y < size.y);
    data(x, y) = EnumUtility::ToChar(entityType);
}

DungeonTagTypes Map::GetCellData(int x, int y) const
{
    assert(x >= 0 && x < size.x && y >= 0 && y < size.y);
    return EnumUtility::ToDungeonTagTypes(data(x, y));
}

//현재 출력되고 있는 맵 데이터를 수집하는 함수. 
void Map::CollectMapData()
{
    Clear();

    auto pairs = ObjectManager::GetInstance()
        .GetComponentTupleVector<DungeonObjectTag, Position>();

    for (auto& [tag, position] : pairs)
    {
        Vector2Int pos = position->GetPosition();
        DungeonTagTypes tagType = tag->GetTag();
        SetCellData(pos.x, pos.y, tagType);
    }
}
void Map::Clear()
{
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            data(x, y) = EnumUtility::ToChar(DungeonTagTypes::None);
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
            SetCellData(static_cast<int>(j), static_cast<int>(i), EnumUtility::ToDungeonTagTypes(line[j]));
        }
    }
}
