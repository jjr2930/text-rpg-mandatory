#include "Slime.h"
#include "Player.h"

#include <iostream>

Slime::Slime(std::string name, int hp, int power, int defence)
    : Monster(name, hp, power, defence)
{
    dropItems.push_back(MonsterDropItem(std::string("슬라임 젤리"), 30));    

    std::cout << "슬라임이 생성되었습니다. (HP: " << hp << ", 공격력: " << power << ", 방어력: " << defence << ")" << std::endl;
}

void Slime::Attack(Player * player)
{
    int realDamage = 0;
    player->Damage(power, &realDamage);

    std::cout << player->GetName() << "에게 " << realDamage << "데미지!" << std::endl;
}
