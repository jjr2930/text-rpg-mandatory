#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <unordered_set>
#include <memory>

using namespace std;

class Object;
class Map;
class Entity;
class VirtualDisplay;

class GameManager
{
public: 
    GameManager();
    void Update();

private:
    std::shared_ptr<Map> map;

    shared_ptr<VirtualDisplay> virtualDisplay;
};

#endif // !GAMEMANAGER_H

