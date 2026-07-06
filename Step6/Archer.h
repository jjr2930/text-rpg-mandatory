#pragma once
#include "Player.h"
class Archer :
    public Player
{
public:
    Archer(std::string& name, int* stats);
    virtual void Attack() override;
    virtual void Attack(Monster* monster) override;
};

