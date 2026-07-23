#include "Dragon.h"
#include "Entity.h"
#include "Stat.h"
#include "Position.h"
#include "Component.h"
#include "DragonStateMachine.h"
#include "EventParameter.h"
#include "Logger.h"

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

void Dragon::TakeDamage(int damage)
{
    int defense = static_cast<int>(stat->GetStat(StatType::Defense));
    int realDamage = damage - defense;

    if (realDamage < 0)
    {
        realDamage = 1;
    }

    stat->AddStat(StatType::CurrentHealth, (float)(-realDamage));
    int currentHealth = static_cast<int>(stat->GetStat(StatType::CurrentHealth));

    if (currentHealth < 0)
    {
        Logger::LogInfo("Dragon is dead!");
        
        DestroyEntity();
    }
}

bool Dragon::IsDead() const
{
    int currentHealth = static_cast<int>(stat->GetStat(StatType::CurrentHealth));
    return currentHealth <= 0;
}

int Dragon::GetExp() const
{
    //TODO, must read from monster table
    return 1000;
}
