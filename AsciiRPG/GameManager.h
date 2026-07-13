#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <unordered_set>
#include <memory>

using namespace std;

class Object;
class Entity;
class VirtualDisplay;
class EventParameter;
class Map;

class GameManager
{
public: 
    GameManager();
    void Update();
    void HandleEvent(shared_ptr<EventParameter> message);
    void CreateCurrentMapObjects();
    void ChangeMap(int newMapIndex);

private:
    shared_ptr<VirtualDisplay> virtualDisplay;
    vector<shared_ptr<Map>> maps;
    int currentMapIndex = 0;
};

#endif // !GAMEMANAGER_H

