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

    normalKeyMap.insert( 
        { 
            { 'w', Virtualkey::w }, { 'W', Virtualkey::W },
            { 's', Virtualkey::s }, { 'S', Virtualkey::S },
            { 'a', Virtualkey::a }, { 'A', Virtualkey::A },
            { 'd', Virtualkey::d }, { 'D', Virtualkey::D },
            { ' ', Virtualkey::Space },
            { 'i', Virtualkey::I }, { 'I', Virtualkey::I },
            { 'e', Virtualkey::E }, { 'E', Virtualkey::E } 
        });

    specialKeyMap.insert(
        { 
            { Const::Key::Up, Virtualkey::Up }, 
            { Const::Key::Down, Virtualkey::Down }, 
            { Const::Key::Left, Virtualkey::Left }, 
            { Const::Key::Right, Virtualkey::Right }, 
            { Const::Key::ESC, Virtualkey::Escape } 
        });
}

void InputController::Update()
{
    if (!_kbhit())
        return;

    Virtualkey virtualKey = Virtualkey::None;

    //support only one input per frame
    char input = _getch();
    if (input == Const::Key::SPECIAL_KEY_PREFIX)
    {
        //consume the next character for special keys
        input = _getch();
        if (specialKeyMap.find(input) == specialKeyMap.end())
        {
            Logger::LogInfo(format("Special key {0} is not in the whitelist.", static_cast<int>(input)));
            return;
        }
        else
        {
            virtualKey = specialKeyMap[input];
        }
    }
    else
    {
        if (normalKeyMap.find(input) == normalKeyMap.end())
        {
            Logger::LogInfo(format("Normal key {0} is not in the whitelist.", input));
            return;
        }
        else
        {
            virtualKey = normalKeyMap[input];
        }
    }

    ObjectManager::GetInstance().BroadcastEvent(std::make_shared<InputEventParameter>(virtualKey));
}