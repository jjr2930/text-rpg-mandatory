#ifndef GENERATIONUTILS_H
#define GENERATIONUTILS_H   

#include "Vector2Int.h"

#include <string>
#include <memory>
class Entity;

using namespace std;

namespace CreationUtil
{
    /*TODO int x, int y => Vector2Int position */

    shared_ptr<Entity> CreatePlayer(Vector2Int position);
    shared_ptr<Entity> CreateMonster(Vector2Int position);
    shared_ptr<Entity> CreateWall(Vector2Int position);
    shared_ptr<Entity> CreateEntrance(Vector2Int position);
    shared_ptr<Entity> CreateExit(Vector2Int position);
    shared_ptr<Entity> CreateFloor(Vector2Int position);
    shared_ptr<Entity> CreateVirtualDisplay();
    shared_ptr<Entity> CreateFieldItem(Vector2Int position, const string& itemName, int quantity);
};

#endif