#include "Monster.h"
#include <iostream>

using namespace std;
MonsterDropItem::MonsterDropItem(std::string& name, int price)
    : dropItemName(name), dropItemPrice(price)
{
}

Monster::Monster(std::string& name, int hp, int power, int defence)
    : name(name), hp(hp), power(power), defence(defence)
{
}

void Monster::Damage(int damage, int* outRealDamage)
{
    *outRealDamage = damage - defence;
    *outRealDamage = (*outRealDamage <= 0) ? 0 : *outRealDamage;

    hp -= *outRealDamage;

    cout << name << "이(가) " << *outRealDamage << " 데미지를 입었습니다. (남은 HP: " << hp << ")" << endl;
}

std::string Monster::GetName() const
{
    return name;
}

int Monster::GetHp() const
{
    return this->hp;
}

int Monster::GetPower() const
{
    return this->power;
}

int Monster::GetDefence() const
{
    return this->defence;
}
