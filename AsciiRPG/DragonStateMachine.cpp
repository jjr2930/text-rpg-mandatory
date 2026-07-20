#include "DragonStateMachine.h"
#include "DragonAttackState.h"
#include "DragonIdleState.h"
#include "DragonMovingState.h"
#include "Logger.h"

#include "GameTime.h"

DragonStateMachine::DragonStateMachine()
    :StateMachine()
{
    BuildTransitionMap();
}

void DragonStateMachine::BuildTransitionMap()
{
    shared_ptr<State> idleState = make_shared<DragonIdleState>();
    shared_ptr<State> movingState = make_shared<DragonMovingState>(1.0);
    shared_ptr<State> attackState = make_shared<DragonAttackState>();

    states.emplace_back(idleState);
    states.emplace_back(movingState);
    states.emplace_back(attackState);

    shared_ptr<Transition> idleToMoving = make_shared<Transition>( idleState, 
        bind(&DragonStateMachine::IdleFinished, this, placeholders::_1), 
        movingState);

    shared_ptr<Transition> movingToAttack = make_shared<Transition>(movingState,
        bind(&DragonStateMachine::MovingFinished, this, placeholders::_1),
        attackState);

    shared_ptr<Transition> attackToIdle = make_shared<Transition>(attackState,
        bind(&DragonStateMachine::AttackFinished, this, placeholders::_1),
        idleState);

    transitionMap.emplace(idleState, idleToMoving);
    transitionMap.emplace(movingState, movingToAttack);
    transitionMap.emplace(attackState, attackToIdle);

    this->startState = idleState;
}

bool DragonStateMachine::IdleFinished(shared_ptr<State> state) const
{
    shared_ptr<DragonIdleState> idleState = dynamic_pointer_cast<DragonIdleState>(state);

    double idleEndTime = idleState->GetEndIdleTime();
    double currentTime = GameTime::GetInstance().GetTime();
    return currentTime >= idleEndTime;
}

bool DragonStateMachine::MovingFinished(shared_ptr<State> state) const
{
    shared_ptr<DragonMovingState> movingState = dynamic_pointer_cast<DragonMovingState>(state);
    bool isArrived = movingState->IsArrived();
    if (isArrived)
    {
        Logger::LogInfo("Dragon has arrived at the player.");
    }   
    return movingState->IsArrived();
}

bool DragonStateMachine::AttackFinished(shared_ptr<State> state) const
{
    return false;
}
