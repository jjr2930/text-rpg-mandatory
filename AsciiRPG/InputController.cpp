#include "InputController.h"
#include "Entity.h"
#include "Position.h"
#include "EventParameter.h"
#include "Const.h"
#include "Logger.h"

#include <conio.h>
#include <format>

InputController::InputController(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    :Component(id, name, params)
{
    //casting
    auto constructParam = static_cast<Component::ConstructionParamterBase*>(params.get());

    this->entity = constructParam->entity;

    if (auto ptr = entity.lock())
        this->playerPositionComponent = ptr->GetComponent<Position>();
}

void InputController::Update()
{
    if (!_kbhit())
        return;

    //support only one input per frame
    char input = _getch();
    Logger::LogInfo(std::format("InputController::Update() - Input received: '{}'", (int)input));
    if (input == Const::Key::SPECIAL_KEY_PREFIX)
    {
        //consume the next character for special keys
        input = _getch();
        Logger::LogInfo(std::format("InputController::Update() - Special key received: '{}'", (int)input));
    }
    switch (input)
    {
        case 'w': case 'W':
        case 's': case 'S':
        case 'a': case 'A':
        case 'd': case 'D':
        case ' ': 
        case 'i': case 'I':
        case 'e': case 'E':
        case Const::Key::Up:
        case const:
        case Const::Key::ESC:
            ObjectManager::GetInstance().BroadcastEvent(std::make_shared<InputEventParameter>(input));
            break;

        default:
            break;
    }
}
