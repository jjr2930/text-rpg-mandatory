#ifndef INPUT_CONTROLLER_H  
#define INPUT_CONTROLLER_H

#include "Component.h"
#include "IConstructionParameter.h"
#include "Enums.h"

#include <unordered_map>

class Entity;
class Position;

using namespace std;

class InputController : public Component
{
public:
    using Component::Component;
    InputController(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void Update();

private:
    shared_ptr<Position> playerPositionComponent;
    unordered_map<char, Virtualkey> normalKeyMap;
    unordered_map<char, Virtualkey> specialKeyMap;
};

#endif // !INPUT_CONTROLLER_H