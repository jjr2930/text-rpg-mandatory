#pragma once
#include "Object.h"
#include "IConstructionParameter.h"
#include "Enums.h"
#include "Vector2Int.h"

#include <vector>
#include <Memory>

using namespace std;

class Entity;
class MapCell;

class Map : public Object
{
public:
    class ConstructionParameter : public IConstructionParameter
    {
    public:
        ConstructionParameter(int width, int height) 
            : width(width), height(height)
        {
        }

    public:
        int width;
        int height;
    };

public:
    Map(int64_t id, const string& name, shared_ptr<IConstructionParameter> params);
    ~Map();

    void AddEntityToCell(int x, int y, shared_ptr<Entity> entity);
    void RemoveEntityFromCell(int x, int y, shared_ptr<Entity> entity);

    Vector2Int GetEntranceCellIndex() const;
    Vector2Int GetExitCellIndex() const;

private:
    MapCell* GetCell(int x, int y);
    MapCell* GetRandomCellWithoutBound();
    MapCell* GetRandomCell(int minX, int maxX, int minY, int maxY);
    MapCell* GetNeighbourCell(int x, int y, Dicrection dir);
    MapCell* GetRandomNeighbourCell(MapCell* cell);
    std::vector<MapCell*> GetNeighbours(int x, int y);
    std::vector<MapCell*> GetNeighbours(Vector2Int position);
    std::vector<MapCell*> GetNeighbours(MapCell* cell);
private:
    std::vector<MapCell*> cells;

    int width;
    int height;

    Vector2Int entranceCellIndex;
    Vector2Int exitCellIndex;   
};

