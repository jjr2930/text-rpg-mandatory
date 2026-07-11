#ifndef WALL_H
#define WALL_H

#include "Component.h"

class EventParameter;

class Wall :public Component
{
public:
    using Component::Component;

    void HandleEvent(shared_ptr<EventParameter> message) override;
};

#endif // !WALL_H