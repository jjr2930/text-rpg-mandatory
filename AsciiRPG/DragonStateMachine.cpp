#include "DragonStateMachine.h"
#include "DragonAttackState.h"
#include "DragonIdleState.h"
#include "DragonMovingState.h"
#include "DragonRangeAttack.h"
#include "Logger.h"
#include "MinMax.h"

#include "GameTime.h"

#include <cassert>

DragonStateMachine::DragonStateMachine()
    :StateMachine()
{
    BuildTransitionMap();
}

void DragonStateMachine::BuildTransitionMap()
{
    shared_ptr<State> idleState = make_shared<DragonIdleState>();
    shared_ptr<State> movingState = make_shared<DragonMovingState>(0.25);
    shared_ptr<State> attackState = make_shared<DragonAttackState>(0.25);
    shared_ptr<State> rangeAttackState = make_shared<DragonRangeAttack>(MinMaxDouble(0.1, 1.0), MinMaxInt(1, 5));

    states.emplace_back(idleState);
    states.emplace_back(movingState);
    states.emplace_back(attackState);
    states.emplace_back(rangeAttackState);

    shared_ptr<Transition> idleToMoving = make_shared<Transition>( idleState, 
        bind(&DragonStateMachine::RollMove, this, placeholders::_1), 
        movingState);

    shared_ptr<Transition> idleToRangeAttack = make_shared<Transition>( idleState, 
        bind(&DragonStateMachine::RollRangeAttack, this, placeholders::_1), 
        rangeAttackState);

    shared_ptr<Transition> movingToAttack = make_shared<Transition>(movingState,
        bind(&DragonStateMachine::MovingFinished, this, placeholders::_1),
        attackState);

    shared_ptr<Transition> attackToIdle = make_shared<Transition>(attackState,
        bind(&DragonStateMachine::MeleeAttackFinished, this, placeholders::_1),
        idleState);

    shared_ptr<Transition> rangeAttackToIdle = make_shared<Transition>(rangeAttackState,
        bind(&DragonStateMachine::RangeAttackFinished, this, placeholders::_1),
        idleState);

    shared_ptr<Transition> movingToIdle = make_shared<Transition>(movingState,
        bind(&DragonStateMachine::MovingTimeout, this, placeholders::_1),
        idleState);

    transitionMap.emplace(idleState, idleToMoving);
    transitionMap.emplace(idleState, idleToRangeAttack);    
    transitionMap.emplace(movingState, movingToAttack);
    transitionMap.emplace(movingState, movingToIdle);
    transitionMap.emplace(attackState, attackToIdle);
    transitionMap.emplace(rangeAttackState, rangeAttackToIdle);

    this->startState = idleState;
}

bool DragonStateMachine::IdleFinished(shared_ptr<State> state) const
{
    shared_ptr<DragonIdleState> idleState = dynamic_pointer_cast<DragonIdleState>(state);

    double idleEndTime = idleState->GetEndIdleTime();
    double currentTime = GameTime::GetInstance().GetNow();

    return currentTime >= idleEndTime;
}

bool DragonStateMachine::RollMove(shared_ptr<State> state) const
{
    shared_ptr<DragonIdleState> idleState = dynamic_pointer_cast<DragonIdleState>(state);
    assert(nullptr != idleState && "state argument must be of type DragonIdleState");

    if (!IdleFinished(state))
        return false;

    int randomNumber = Random::GetInstance().RandomRange(0, 1);
    int remainder = randomNumber % 2;

    if (remainder == 0)
    {
        Logger::LogInfo("DragonStateMachine::RollMove() -> true");
    }
    else
    {
        Logger::LogInfo("DragonStateMachine::RollMove() -> false");
    }

    return remainder == 0;
}

bool DragonStateMachine::RollRangeAttack(shared_ptr<State> state) const
{
    shared_ptr<DragonIdleState> idleState = dynamic_pointer_cast<DragonIdleState>(state);
    assert(nullptr != idleState && "state argument must be of type DragonIdleState");

    if (!IdleFinished(state))
        return false;

    int randomNumber = Random::GetInstance().RandomRange(0, 1);
    int remainder = randomNumber % 2;

    if (remainder == 1)
    {
        Logger::LogInfo("DragonStateMachine::RollRangeAttack() -> true");
    }
    else
    {
        Logger::LogInfo("DragonStateMachine::RollRangeAttack() -> false");
    }

    return remainder == 1;
}

bool DragonStateMachine::MovingFinished(shared_ptr<State> state) const
{
    shared_ptr<DragonMovingState> movingState = dynamic_pointer_cast<DragonMovingState>(state);
    assert(nullptr != movingState && "state argument must be of type DragonMovingState");

    return movingState->IsArrived();
}

bool DragonStateMachine::MeleeAttackFinished(shared_ptr<State> state) const
{
    shared_ptr<DragonAttackState> attackState = dynamic_pointer_cast<DragonAttackState>(state);
    assert(nullptr != attackState && "state argument must be of type DragonAttackState");

    if(attackState->OutOfRangeWithPlayer())
    {
        return true;
    }
    return false;
}

bool DragonStateMachine::RangeAttackFinished(shared_ptr<State> state) const
{
    shared_ptr<DragonRangeAttack> rangeAttackState = dynamic_pointer_cast<DragonRangeAttack>(state);
    assert(nullptr != rangeAttackState && "state argument must be of type DragonRangeAttack");

    return rangeAttackState->IsShootingFinished();
}

bool DragonStateMachine::MovingTimeout(shared_ptr<State> state) const
{
    shared_ptr<DragonMovingState> movingState = dynamic_pointer_cast<DragonMovingState>(state);
    assert(nullptr != movingState && "state argument must be of type DragonMovingState");

    return movingState->IsTimeout();
}
