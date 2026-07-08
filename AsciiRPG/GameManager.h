#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <unordered_set>
#include <memory>

using namespace std;

class Object;
class Map;
class Entity;

class GameManager
{
public: 
    GameManager();
    void Update();

private:
    std::unordered_set<std::shared_ptr<Entity>> entities;
    std::shared_ptr<Map> map;
};

#endif // !GAMEMANAGER_H

