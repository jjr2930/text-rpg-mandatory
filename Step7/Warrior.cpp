#include "Warrior.h"
#include "Const.h"
#include "Monster.h"

#include <iostream>

using namespace std;

Warrior::Warrior(std::string& name, int* stats)
    : Player(name, stats)
{
    job = JobType::Warrior;
    hp += Const::PLAYER::SPCECIAL_STAT_INCREASE_AMOUNT;
    defence += Const::PLAYER::SPCECIAL_STAT_INCREASE_AMOUNT;


    cout << GetJobName() << "로 전직하였습니다. (HP + " << Const::PLAYER::SPCECIAL_STAT_INCREASE_AMOUNT << ", 방어력 + " << Const::PLAYER::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Warrior::Attack()
{
    cout << "검을 사용하여 적을 공격합니다. 공격력: " << power << endl;
}

void Warrior::Attack(Monster* monster)
{
    int realDamage = 0;
    monster->Damage(power, &realDamage);

    cout << monster->GetName() << "에게 " << realDamage << "데미지!" << endl;
}
