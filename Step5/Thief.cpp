#include "Thief.h"
#include "Const.h"
#include "Monster.h"

#include <iostream>

using namespace std;

Thief::Thief(std::string& name, int* stats)
    : Player(name, stats)
{
    power += Const::SPCECIAL_STAT_INCREASE_AMOUNT;

    cout << "* " << GetJobName() << "濡??꾩쭅?섏??듬땲?? (怨듦꺽??+ " << Const::SPCECIAL_STAT_INCREASE_AMOUNT << " )" << endl;
}

void Thief::Attack()
{
    cout << "?④????ъ슜?섏뿬 ?곸쓣 怨듦꺽?⑸땲?? 怨듦꺽?? " << power << endl;
}

void Thief::Attack(Monster* monster)
{
    int realDamage = 0;
    monster->Damage(power, &realDamage);

    cout << monster->GetName() << "?먭쾶 " << realDamage << "?곕?吏!" << endl;
}
