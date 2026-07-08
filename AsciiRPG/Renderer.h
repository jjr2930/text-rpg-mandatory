#pragma once
#include "Component.h"
#include "IConstructionParameter.h"
#include "Vector2Int.h"

class Position;
class Entity;

using namespace std;

class Renderer : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(char toPrint, shared_ptr<Entity> entity) 
            : Component::ConstructionParamterBase(entity)
        {
            this->toPrint = toPrint;
        }

        char toPrint;
    };

public :
    using Component::Component;
    Renderer(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    char GetToPrint() const;
    Vector2Int GetPosition() const;

private:
    char toPrint;
    shared_ptr<Position> position;
};

