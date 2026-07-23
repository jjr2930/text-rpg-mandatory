#ifndef GENERATIONUTILS_H
#define GENERATIONUTILS_H   

#include <string>
#include <memory>

#include "Vector2Int.h"

class Entity;
class Map;
class IItem;

using namespace std;

namespace CreationUtil
{
    /*TODO int x, int y => Vector2Int position */

    shared_ptr<Entity> CreatePlayer(Vector2Int position);
    shared_ptr<Entity> CreateWall(Vector2Int position);
    shared_ptr<Entity> CreateEntrance(Vector2Int position);
    shared_ptr<Entity> CreateExit(Vector2Int position);
    shared_ptr<Entity> CreateFloor(Vector2Int position);
    shared_ptr<Entity> CreateVirtualDisplay();
    shared_ptr<Entity> CreateFieldItem(Vector2Int position, shared_ptr<IItem> item, int quantity);
    shared_ptr<Entity> CreateNpc(Vector2Int position);
    shared_ptr<Entity> CreateMonsterBase(Vector2Int position, char displayChar);
    shared_ptr<Entity> CreateNormalMonster(Vector2Int position, char displayChar);
    shared_ptr<Entity> CreateDragon(Vector2Int position);
    shared_ptr<Entity> CreateDragonBullet(Vector2Int position, Vector2Int targetPosition, int damage);
    shared_ptr<Map> CreateDragonRoom();
    shared_ptr<Map> CreateTownMap();

};

#endif