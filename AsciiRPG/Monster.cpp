#include "Monster.h"
#include "ObjectManager.h"
#include "Logger.h"
#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "MathUtility.h"
#include "MonsterItemDropTable.h"
#include "Stat.h"

#include <format>

using namespace std;

Monster::Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    MonsterConstructionParameter* constructionParams = static_cast<MonsterConstructionParameter*>(params.get());
    dropItems = MonsterItemDropTable::GetInstance().GetDropItems(constructionParams->dropTableKey);
    
    if (auto ptr = entity.lock())
    {
        monsterPosition = ptr->GetComponent<Position>();
        monsterStat = ptr->GetComponent<Stat>();
    }
}

void Monster::TakeDamage(int damage)
{
    int defense = monsterStat->GetStat(StatType::Defense);
    int realDamage = damage - defense;
    if (realDamage < 0)
    {
        realDamage = 0;
    }

    monsterStat->AddStat(StatType::CurrentHealth, -realDamage);
   
    auto currentHealth = monsterStat->GetStat(StatType::CurrentHealth);
    if (currentHealth <= 0)
    {
        if (auto ptr = entity.lock())
        {
            Logger::LogInfo(format("{} is dead!", ptr->GetName()));
            ObjectManager::GetInstance().DestroyEntity(ptr);
        }
    }
}

int Monster::GetExp() const
{
    return monsterStat->GetStat(StatType::Exp);
}

bool Monster::IsDead() const
{
    int currentHp = monsterStat->GetStat(StatType::CurrentHealth);
    return currentHp <= 0;
}

shared_ptr<MonsterItemDropData> Monster::RollDropTable() const
{
    double totalRange = 0.0;
    for(auto& element : dropItems)
        totalRange += element->dropChance;

    double random = Random::GetInstance().RandomRange(0.0, totalRange);
    double elapsed = 0.0;
    for (auto& element : dropItems)
    {
        elapsed += element->dropChance;
        if (random <= elapsed)
            return element;
    }

    return nullptr;
}


void Monster::Update()
{
}

void Monster::HandleEvent(shared_ptr<EventParameter> message)
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
