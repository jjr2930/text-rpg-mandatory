#include "Warrior.h"
#include "Const.h"
#include <iostream>

using namespace std;

Warrior::Warrior(std::string& name, int* stats)
    : Player(name, stats)
{
    hp += Const::SPCECIAL_STAT_INCREASE_AMOUNT;
    defence += Const::SPCECIAL_STAT_INCREASE_AMOUNT;


    cout << GetJobName() << "로 전직하였습니다. (HP + " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << ", 방어력 + " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Warrior::Attack()
{
    cout << "검을 사용하여 적을 공격합니다. 공격력: " << power << endl;
}
