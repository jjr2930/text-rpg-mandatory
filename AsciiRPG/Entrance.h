#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Component.h"
#include <memory>

using namespace std;

class Position;

class Entrance : public Component
{
public:
    using Component::Component;
    Entrance(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
 
    shared_ptr<Position> myPosition;
    bool previousOverlap = false;
    bool playerEntered = false;
    bool active = false;
};


#endif // !ENTRANCE_H