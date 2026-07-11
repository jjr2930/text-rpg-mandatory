#include "Renderer.h"
#include "Entity.h"
#include "Position.h"

#include <iostream>

using namespace std;

Renderer::Renderer(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    :Component(id, name, params)
{
    ConstructionParameter* constructParam = static_cast<ConstructionParameter*>(params.get());
    this->toPrint = constructParam->toPrint;

    if (auto ptr = entity.lock())
        this->position = ptr->GetComponent<Position>();
}

char Renderer::GetToPrint() const
{
    return toPrint;
}

Vector2Int Renderer::GetPosition() const
{
    return position->GetPosition();
}
