#include "Thief.h"
#include "Const.h"
#include "Monster.h"

#include <iostream>

using namespace std;

Thief::Thief(std::string& name, int* stats)
    : Player(name, stats)
{
    power += Const::PLAYER::SPCECIAL_STAT_INCREASE_AMOUNT;

    cout << "* " << GetJobName() << "로 전직하였습니다. (공격력 + " << Const::PLAYER::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Thief::Attack()
{
    cout << "단검을 사용하여 적을 공격합니다. 공격력: " << power << endl;
}

void Thief::Attack(Monster* monster)
{
    int realDamage = 0;
    monster->Damage(power, &realDamage);

    cout << monster->GetName() << "에게 " << realDamage << "데미지!" << endl;
}
