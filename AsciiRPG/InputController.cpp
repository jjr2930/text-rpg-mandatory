#include "InputController.h"
#include "Entity.h"
#include "Position.h"

#include <conio.h>

InputController::InputController(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    :Component(id, name, params)
{
    //casting
    auto constructParam = static_cast<Component::ConstructionParamterBase*>(params.get());

    this->entity = constructParam->entity;
    this->playerPositionComponent = entity->GetComponent<Position>();
}

void InputController::Update()
{
    if (!_kbhit())
        return;

    //support only one input per frame
    char input = _getch();
    switch (input)
    {
        case 'w':
            playerPositionComponent->TryMoveYOnly(-1);
            break;

        case 's':
            playerPositionComponent->TryMoveYOnly(1);
            break;  

        case 'a':
            playerPositionComponent->TryMoveXOnly(-1);
            break;

        case 'd':
            playerPositionComponent->TryMoveXOnly(1);
            break;

        default:
            break;
    }
}
