#ifndef TRANSITION_H
#define TRANSITION_H

#include <memory>
#include <functional>

#define TRANSITION_CALLBACK   function<bool(shared_ptr<State>currentState)>

class State;

using namespace std;

class Transition
{
public:
    Transition(shared_ptr<State> fromState, TRANSITION_CALLBACK callback, shared_ptr<State> toState);

    bool CanTransition();
    shared_ptr<State> GetToState() const;
private:
    shared_ptr<State> fromState;
    TRANSITION_CALLBACK callback;
    shared_ptr<State> toState;
};

#endif // !TRANSITION_H

