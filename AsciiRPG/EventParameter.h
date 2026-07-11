#ifndef EVENT_PARAMETER_H
#define EVENT_PARAMETER_H

#include "Enums.h"

class EventParameter
{
public:
    EventType eventType;
};

class InputEventParameter : public EventParameter
{
public:
    InputEventParameter(char inputChar)
    {
        this->eventType = EventType::KeyPressed;
        this->inputChar = inputChar;
    }
    char inputChar;
};

#endif // !EVENT_PARAMETER_H
