#include "Transition.h"

Transition::Transition(shared_ptr<State> fromState, TRANSITION_CALLBACK callback, shared_ptr<State> toState)
    : fromState(fromState), callback(callback), toState(toState)
{}

bool Transition::CanTransition()
{
    return callback(fromState);
}

shared_ptr<State> Transition::GetToState() const
{
    return toState;
}
