#include "Magician.h"
#include "Const.h"
#include "Monster.h"

#include <iostream>

using namespace std;

Magician::Magician(std::string& name, int* stats)
    : Player(name, stats)
{
    job = JobType::Magician;

    mp += Const::SPCECIAL_STAT_INCREASE_AMOUNT;

    cout << "* " << GetJobName() << "로 전직하였습니다. (MP + " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Magician::Attack()
{
    cout << "마법을 사용하여 적을 공격합니다. 공격력: " << power << endl;
}

void Magician::Attack(Monster* monster)
{
    int realDamage = 0;

    monster->Damage(power, &realDamage);

    cout << monster->GetName() << "에게 " << realDamage << "데미지!" << endl;
}
