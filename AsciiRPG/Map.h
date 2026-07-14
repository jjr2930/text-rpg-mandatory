#pragma once
#include "Object.h"
#include "Enums.h"
#include "Vector2Int.h"

#include <vector>
#include <Memory>

using namespace std;

class Entity;

class Map
{
public:
    Map(int width, int height);
    ~Map();

    void SetCellData(int x, int y, char data);
    char GetCellData(int x, int y) const;
    void CollectMapData();
    void Clear();
    void From(const vector<string>& source);

    //void AddEntityToCell(int x, int y, shared_ptr<Entity> entity);
    //void RemoveEntityFromCell(int x, int y, shared_ptr<Entity> entity);

    //Vector2Int GetEntranceCellIndex() const;
    //Vector2Int GetExitCellIndex() const;

private:
    //MapCell* GetCell(int x, int y);
    //MapCell* GetRandomCellWithoutBound();
    //MapCell* GetRandomCell(int minX, int maxX, int minY, int maxY);
    //MapCell* GetNeighbourCell(int x, int y, Dicrection dir);
    //MapCell* GetRandomNeighbourCell(MapCell* cell);
    //std::vector<MapCell*> GetNeighbours(int x, int y);
    //std::vector<MapCell*> GetNeighbours(Vector2Int position);
    //std::vector<MapCell*> GetNeighbours(MapCell* cell);
private:
    char* rawData;

    //std::vector<MapCell*> cells;

    Vector2Int size;

    Vector2Int entranceCellIndex;
    Vector2Int exitCellIndex;   
};

