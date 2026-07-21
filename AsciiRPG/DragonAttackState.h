#ifndef DRAGON_ATTACK_STATE_H
#define DRAGON_ATTACK_STATE_H

#include <memory>

#include "State.h"

using namespace std;

class Player;
class Dragon;
class Stat;
class Position;

/// <summary>
/// TODO: Name change to DragonMeleeAttackState
/// </summary>
class DragonAttackState : public State
{
public:
    using State::State;    
    DragonAttackState(double attackDelay);

    void Start() override;
    void Update() override;

    bool OutOfRangeWithPlayer() const;
private:
    shared_ptr<Stat> stat;
    shared_ptr<Player>      player;
    shared_ptr<Position>    playerPosition;
    shared_ptr<Stat>        playerStat;
    shared_ptr<Dragon>      dragon;
    shared_ptr<Position>    dragonPosition;
    shared_ptr<Stat>        dragonStat;

    double lastAttackTime = 0.0;
    double attackDelay = 1.0;
};

#endif // !DRAGON_ATTACK_STATE_H
