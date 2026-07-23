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
    void CreateCurrentMapObjects(bool goingToDown);
    void ChangeMap(int newMapIndex);

private:
    shared_ptr<VirtualDisplay> virtualDisplay;
    vector<shared_ptr<Map>> maps;
    unordered_set<char> validMonsterChars;

    int currentMapIndex = 0;
};

#endif // !GAMEMANAGER_H

