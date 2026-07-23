#pragma once
#include "Monster.h"
class NormalMonster : public Monster
{
public:
    using Monster::Monster;

    void Update() override;

private:
    bool fistOverlap;
    double nextAttackTime;
};

