#pragma once
#include "Component.h"
class Monster : public Component
{
public:
    using Component::Component;

    void TakeDamage(int damage);

private:
    int hp;
    int attack;
    int defense;
};

