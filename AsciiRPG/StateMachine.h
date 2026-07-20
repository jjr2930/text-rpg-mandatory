#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

#include "Transition.h"

class State;

using namespace std;

class StateMachine
{
public:
    virtual void BuildTransitionMap() = 0;
    void Start();
    void Update();
    void End();

protected:
    unordered_multimap<shared_ptr<State>, shared_ptr<Transition>> transitionMap;

    vector<shared_ptr<State>> states;
    shared_ptr<State> currentState;
    shared_ptr<State> startState;
};

#endif // !STATE_MACHINE_H
