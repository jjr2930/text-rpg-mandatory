#include "Monster.h"
#include "ObjectManager.h"
#include "Logger.h"

Monster::Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    MonsterConstructionParameter* constructionParams = static_cast<MonsterConstructionParameter*>(params.get());
    hp = constructionParams->hp;
    attack = constructionParams->attack;
    defense = constructionParams->defense;

    dropItems = constructionParams->dropItems;
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
