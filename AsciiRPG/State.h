#ifndef STATE_H
#define STATE_H

class State
{
public:
    virtual void Start() {}
    virtual void Update() {}
    virtual void End() {}
};

#endif // !STATE_H
