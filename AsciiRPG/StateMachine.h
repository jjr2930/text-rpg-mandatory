#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>
#include <memory>
#include <unordered_map>

class State;

using namespace std;

class StateMachine
{
public:
    virtual void BuildTransitionMap();
    virtual void AddEvent(int event);

private:
    vector<shared_ptr<State>> states;
    unordered_map<shared_ptr<State>, unordered_map<int, shared_ptr<State>>> transitionMap;
};

#endif // !STATE_MACHINE_H
