#include "StateMachine.h"
#include "State.h"
#include "Transition.h"

#include <cassert>

void StateMachine::Start()
{
    assert(nullptr != startState && "Start state must be set before starting the state machine.");
    
    currentState = startState;
    currentState->Start();
}

void StateMachine::Update()
{
    assert(nullptr != currentState && "Current state must be set before updating the state machine.");

    currentState->Update();
    const auto& range = transitionMap.equal_range(currentState);
    for (auto it = range.first; it != range.second; ++it)
    {
        auto& transition = it->second;
        if (transition->CanTransition())
        {
            currentState->End();
            currentState = transition->GetToState();
            currentState->Start();
            break;
        }
    }
}

void StateMachine::End()
{
    assert(nullptr != currentState && "Current state must be set before ending the state machine.");
    
    currentState->End();
}
