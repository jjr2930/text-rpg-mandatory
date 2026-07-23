#include "Dragon.h"
#include "Entity.h"
#include "Stat.h"
#include "Position.h"
#include "Component.h"
#include "DragonStateMachine.h"
#include "EventParameter.h"
#include "Logger.h"

Dragon::Dragon(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Monster(id, name, params)
{
    if (auto ptr = entity.lock())
    {
        stat = ptr->GetComponent<Stat>();
        position = ptr->GetComponent<Position>();
        stateMachine = std::make_shared<DragonStateMachine>();
    }
}

void Dragon::Start()
{
    stateMachine->Start();
}

void Dragon::Update()
{
    stateMachine->Update();
}

void Dragon::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnMapClearRequested:
            DestroyEntity();
            break;

        default:
            break;
    }
}