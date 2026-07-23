#ifndef DRAGON_H
#define DRAGON_H

#include "Component.h"
#include "Monster.h"

#include <memory>

using namespace std;

class Stat;
class Position;
class DragonStateMachine;

class Dragon : public Monster
{
public:
    using Monster::Monster;
    Dragon(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    void Start() override;
    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
    shared_ptr<Stat> stat;
    shared_ptr<Position> position;
    shared_ptr<DragonStateMachine> stateMachine;
};

#endif