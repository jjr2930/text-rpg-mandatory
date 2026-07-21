#ifndef BOSS_STATE_MACHINE_H
#define BOSS_STATE_MACHINE_H

#include "StateMachine.h"

class DragonStateMachine : public StateMachine
{
public:
    DragonStateMachine();
    void BuildTransitionMap() override;

    bool IdleFinished(shared_ptr<State> state) const;
    /// <summary>
    /// TODO : Has same codeblock with RollRangeAttack. Consider refactoring to a single function.
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    bool RollMove(shared_ptr<State> state) const;
    bool RollRangeAttack(shared_ptr<State> state) const;
    bool MovingFinished(shared_ptr<State> state) const;
    /// <summary>
    /// TODO: Name change to MeleeAttackFinished
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    bool MeleeAttackFinished(shared_ptr<State> state) const;
    bool RangeAttackFinished(shared_ptr<State> state) const;
    bool MovingTimeout(shared_ptr<State> state) const;
};

#endif // !BOSS_STATE_MACHINE_H