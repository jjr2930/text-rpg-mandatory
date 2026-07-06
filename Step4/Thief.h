#pragma once
#include "Player.h"
class Thief :
    public Player
{
public:
    Thief(std::string& name, int* stats);
    virtual void Attack() override;
};

