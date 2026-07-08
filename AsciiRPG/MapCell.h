#ifndef MAPCELL_H
#define MAPCELL_H

#include <vector>
#include <memory>   
#include "Vector2Int.h"
#include "Enums.h"

class Object;
class Entity;

class MapCell
{

public:
    MapCell(int x, int y);
    void AddEntity(std::shared_ptr<Entity> entity);
    void RemoveEntity(std::shared_ptr<Entity> entity);
    bool HasWall();
    bool HasFloor();
    bool HasMonster();
    int GetEntityCount() const;

    Vector2Int GetPosition() const;
    int GetX() const;
    int GetY() const;

private:
    Vector2Int position;
    std::vector<std::shared_ptr<Entity>> entities;
};

#endif // !MAPCELL_H