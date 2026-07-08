#pragma once

#include "Component.h"
#include "IConstructionParameter.h"
class Entity;
class Position;

class InputController : public Component
{
public:
    using Component::Component;
    InputController(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void Update();

private:
    shared_ptr<Position> playerPositionComponent;
};

