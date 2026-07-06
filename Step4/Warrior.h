#pragma once
#include "Player.h"
class Warrior :
    public Player
{
public:
    Warrior(std::string& name, int* stats);
    virtual void Attack() override;
};
