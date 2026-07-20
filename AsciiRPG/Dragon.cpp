#include "Dragon.h"
#include "Entity.h"
#include "Stat.h"
#include "Position.h"
#include "Component.h"
#include "DragonStateMachine.h"

Dragon::Dragon(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
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
