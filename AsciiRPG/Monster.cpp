#include "Monster.h"
#include "ObjectManager.h"

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
