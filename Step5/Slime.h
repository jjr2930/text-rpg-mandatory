#pragma once
#include "Monster.h"
class Slime : public Monster
{
public:
    Slime(std::string name, int hp, int power, int defence);
    virtual void Attack(class Player* player) override;
};

