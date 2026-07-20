#ifndef BOSS_IDLE_STATE_H
#define BOSS_IDLE_STATE_H

#include "State.h"
#include "Vector2.h"
#include "MinMax.h"


#include <memory>

using namespace std;

class Position;

class DragonIdleState :  public State
{
public :
    void Start() override;

    double GetEndIdleTime() const;

private:
    MinMaxDouble idleDurationRange{ 0.0, 1.0 };
    double endIdleTime;
};

#endif // BOSS_IDLE_STATE_H