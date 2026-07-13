#include "Thief.h"
#include "Const.h"
#include <iostream>

using namespace std;

Thief::Thief(std::string& name, int* stats)
    : Player(name, stats)
{
    job = JobType::Thief;

    power += Const::SPCECIAL_STAT_INCREASE_AMOUNT;

    cout << "* " << GetJobName() << "로 전직하셨습니다. 힘이 " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << " 증가합니다." << endl;
}

void Thief::Attack()
{
    cout << GetJobName() << "가 공격합니다. 공격력: " << power << endl;
}
