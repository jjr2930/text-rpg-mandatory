#include "Monster.h"
#include "ObjectManager.h"
#include "Logger.h"
#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "MathUtility.h"
#include "MonsterItemDropTable.h"

Monster::Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    MonsterConstructionParameter* constructionParams = static_cast<MonsterConstructionParameter*>(params.get());
    hp = constructionParams->hp;
    attack = constructionParams->attack;
    defense = constructionParams->defense;
    exp = constructionParams->exp;
    dropItems = MonsterItemDropTable::GetInstance().GetDropItems(constructionParams->dropTableKey);
    attackDelay = constructionParams->attackDelay;
    
    if (auto ptr = entity.lock())
        monsterPosition = ptr->GetComponent<Position>();
}

void Monster::TakeDamage(int damage)
{
    int realDamage = damage - defense;
    if (realDamage < 0)
    {
        realDamage = 0;
    }

    hp -= realDamage;

    if (hp <= 0)
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
    return exp;
}

bool Monster::IsDead() const
{
    return hp <= 0;
}

vector<shared_ptr<MonsterItemDropData>>& Monster::GetDropItems()
{
    return dropItems;
}

void Monster::Update()
{
    auto [player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
    if (!player || !playerPosition)
    {
        Logger::LogError("There should be exactly one player in the game.");
        return;
    }

    Vector2Int myPosition = monsterPosition->GetPosition();

    if (!MathUtility::IsOverlap(myPosition, playerPosition->GetPosition(), 1))
    {
        fistOverlap = false;
        return;
    }
    
    if(!fistOverlap)
    {
        fistOverlap = true;
        nextAttackTime = DateTime::Now();
        nextAttackTime.AddSeconds(attackDelay);
    }

    else if(DateTime::Now() >= nextAttackTime)
    {
        Logger::LogError(format("{} attacks({}) you", name, attack));
        player->TakeDamage(attack);
        nextAttackTime = DateTime::Now();
        nextAttackTime.AddSeconds(attackDelay);
    }    
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
