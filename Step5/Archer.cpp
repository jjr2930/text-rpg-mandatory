#include "Archer.h"
#include "Const.h"
#include "Monster.h"

#include <iostream>

using namespace std;

Archer::Archer(std::string& name, int* stats)
    :Player(name, stats)
{
    job = JobType::Archer;

    power += Const::SPCECIAL_STAT_INCREASE_AMOUNT;

    cout << "* " << GetJobName() << "로 전직하였습니다. (공격력 + " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Archer::Attack()
{
    cout << "활을 사용하여 적을 공격합니다. 공격력: " << power << endl;
}

void Archer::Attack(Monster* monster)
{
    int realDamage = 0;
    monster->Damage(power, &realDamage);

    cout << monster->GetName() << "에게 " << realDamage << "데미지!" << endl;
}
