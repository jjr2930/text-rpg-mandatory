#ifndef EVENT_PARAMETER_H
#define EVENT_PARAMETER_H

#include "Enums.h"

class InteractableObject;

class EventParameter
{
public:
    EventType eventType;
};

class InputEventParameter : public EventParameter
{
public:
    InputEventParameter(Virtualkey key)
        : key(key)
    {
        this->eventType = EventType::KeyPressed;
    }

    Virtualkey key;
};

class InteractionStartEventParameter : public EventParameter
{
public:
    InteractionStartEventParameter(std::shared_ptr<InteractableObject> interactableObject)
        : EventParameter()
        , interactableObject(interactableObject)
    {
        this->eventType = EventType::OnStartInteraction;
    }   

    std::shared_ptr<InteractableObject> interactableObject;
};

class InteractionCanceledEventParameter : public EventParameter
{
public:
    InteractionCanceledEventParameter()
        : EventParameter()
    {
        this->eventType = EventType::OnStopInteraction;
    }
};

#endif // !EVENT_PARAMETER_H