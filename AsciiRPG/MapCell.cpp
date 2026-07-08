#include "MapCell.h"
#include "Object.h"
#include "Entity.h"
#include "Renderer.h"
#include "Wall.h"
#include "Floor.h"
#include "Monster.h"

#include <iostream>

using namespace std;


MapCell::MapCell(int x, int y)
    : position(x, y)
{
}

void MapCell::AddEntity(std::shared_ptr<Entity> entity  )
{
    entities.push_back(entity);
}

void MapCell::RemoveEntity(std::shared_ptr<Entity> entity)
{
    for (auto iter = entities.begin(); iter != entities.end(); ++iter)
    {
        if ((*iter)->GetId() == entity->GetId())
        {
            entities.erase(iter);
            return;
        }
    }
}

bool MapCell::HasWall()
{
    for (auto& entity : entities)
    {
        std::shared_ptr<Wall> renderer;
        if (entity->TryGetComponent(renderer))
            return true;
    }
    return false;
}

bool MapCell::HasFloor()
{
    for (auto& entity : entities)
    {
        std::shared_ptr<Floor> renderer;
        if (entity->TryGetComponent(renderer))
            return true;
    }
    return false;
}

bool MapCell::HasMonster()
{
    for (auto& entity : entities)
    {
        std::shared_ptr<Monster> monster;
        if (entity->TryGetComponent(monster))
            return true;
    }
    return false;
}

int MapCell::GetEntityCount() const
{
    return static_cast<int>(entities.size());
}

Vector2Int MapCell::GetPosition() const
{
    return position;
}

int MapCell::GetX() const
{
    return position.x;
}

int MapCell::GetY() const
{
    return position.y;
}
