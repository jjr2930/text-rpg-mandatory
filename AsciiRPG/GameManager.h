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

class GameManager
{
public: 
    GameManager();
    void Update();
    void HandleEvent(shared_ptr<EventParameter> message);
    void CreateNewMap();

private:
    shared_ptr<VirtualDisplay> virtualDisplay;
};

#endif // !GAMEMANAGER_H

