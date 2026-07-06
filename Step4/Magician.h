#pragma once
#include "Player.h"
class Magician :
    public Player
{
public:
    Magician(std::string& name, int* stats);
    virtual void Attack() override;
};

