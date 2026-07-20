#ifndef BOSS_STATE_MACHINE_H
#define BOSS_STATE_MACHINE_H

#include "StateMachine.h"

class DragonStateMachine : public StateMachine
{
public:
    DragonStateMachine();
    void BuildTransitionMap() override;

    bool IdleFinished(shared_ptr<State> state) const;
    bool MovingFinished(shared_ptr<State> state) const;
    bool AttackFinished(shared_ptr<State> state) const;
};

#endif // !BOSS_STATE_MACHINE_H