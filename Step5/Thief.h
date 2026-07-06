#ifndef THIEF_H
#define THIEF_H

#include "Player.h"
class Thief :
    public Player
{
public:
    Thief(std::string& name, int* stats);
    virtual void Attack() override;
    virtual void Attack(Monster* monster) override;
};


#endif // !THIEF_H