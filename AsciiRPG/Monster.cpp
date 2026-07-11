#include "Monster.h"
#include "ObjectManager.h"
#include "Logger.h"
#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "MathUtility.h"

Monster::Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    MonsterConstructionParameter* constructionParams = static_cast<MonsterConstructionParameter*>(params.get());
    hp = constructionParams->hp;
    attack = constructionParams->attack;
    defense = constructionParams->defense;
    exp = constructionParams->exp;
    dropItems = constructionParams->dropItems;
    attackDelay = constructionParams->attackDelay;
    monsterPosition = entity->GetComponent<Position>();
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
        ObjectManager::GetInstance().DestroyEntity(entity);
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

vector<DropItemData>& Monster::GetDropItems()
{
    return dropItems;
}

void Monster::Update()
{
    auto components = ObjectManager::GetInstance().GetComponentsWithTypes<Player, Position>();
    if (components.size() != 1)
    {
        Logger::LogError("There should be exactly one player in the game.");
        return;
    }

    Vector2Int myPosition = monsterPosition->GetPosition();

    auto& [player, playerPosition] = components[0];
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
        Logger::LogError(format("{} attacks player for {} damage", name, attack));
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
            ObjectManager::GetInstance().DestroyEntity(entity);
            break;
        default:
            break;
    }
}
