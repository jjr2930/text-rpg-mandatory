#include "Archer.h"
#include "Const.h"
#include <iostream>

using namespace std;

Archer::Archer(std::string& name, int* stats)
    :Player(name, stats)
{
    power += Const::SPCECIAL_STAT_INCREASE_AMOUNT;

    cout << "* " << GetJobName() << "로 전직하였습니다. (공격력 + " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Archer::Attack()
{
    cout << "활을 사용하여 적을 공격합니다. 공격력: " << power << endl;
}
