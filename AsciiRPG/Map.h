#pragma once
#include "Object.h"
#include "Enums.h"
#include "Vector2Int.h"
#include "json.hpp"
#include "Array2D.h"

#include <vector>
#include <Memory>

using namespace std;
using json = nlohmann::json;

class Entity;
struct MapCell 
{
    Vector2Int position;
    DungeonTagTypes entityType = DungeonTagTypes::None;
};

class Map
{
public:
    Map(int width, int height);
    ~Map() = default;

    void SetCellData(int x, int y, DungeonTagTypes entityType);
    DungeonTagTypes GetCellData(int x, int y) const;
    void CollectMapData();
    void Clear();
    void From(const vector<string>& source);

private:
    Array2D<char> data;

    Vector2Int size;
    Vector2Int entranceCellIndex;
    Vector2Int exitCellIndex;   
};