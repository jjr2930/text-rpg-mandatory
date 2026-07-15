#include "StateMachine.h"

void StateMachine::AddState(shared_ptr<State> state)
{
    states.emplace_back(state);
}

void StateMachine::BuildTransitionMap()
{}
