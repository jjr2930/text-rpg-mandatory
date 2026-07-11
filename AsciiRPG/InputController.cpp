#include "InputController.h"
#include "Entity.h"
#include "Position.h"
#include "EventParameter.h"

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
        case 's':
        case 'a':
        case 'd':
        case ' ':
        case 'i':
            ObjectManager::GetInstance().BroadcastEvent(std::make_shared<InputEventParameter>(input));
            break;

        default:
            break;
    }
}
