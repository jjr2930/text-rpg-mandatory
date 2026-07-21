#ifndef DRAGON_RANGE_ATTACK
#define DRAGON_RANGE_ATTACK

#include <memory>

#include "State.h"
#include "MinMax.h"

using namespace std;

class Stat;
class Position;

/// <summary>
/// TODO : change name to DragonRangeAttackState
/// </summary>
class DragonRangeAttack : public State
{
public:
    using State::State;

    DragonRangeAttack(MinMaxDouble attackDelayRange, MinMaxInt attackCountRange);

    void Start() override;
    void Update() override;

    bool AmIDead() const;
    bool IsShootingFinished() const;
private:
    MinMaxDouble attackDelayRange;
    MinMaxInt attackCountRange;
    int totalAttackCount = 0;
    int currentAttackCount = 0;
    double attackDelay = 0;
    double lastAttackTime = 0.0;
    shared_ptr<Position> playerPosition;
    shared_ptr<Position> dragonPosition;
    shared_ptr<Stat> dragonStat;
};

#endif // !DRAGON_RANGE_ATTACK
