#ifndef DRAGON_ATTACK_STATE_H
#define DRAGON_ATTACK_STATE_H

#include <memory>

#include "State.h"

using namespace std;

class Stat;
class Position;

class DragonAttackState : public State
{
public:
    using State::State;    

    void Start() override;
    void Update() override;

    bool OutOfRangeWithPlayer() const;
private:
    shared_ptr<Stat> stat;
    shared_ptr<Position>    playerPosition;
    shared_ptr<Stat>        playerStat;
    shared_ptr<Position>    dragonPosition;
    shared_ptr<Stat>        dragonStat;
};

#endif // !DRAGON_ATTACK_STATE_H
