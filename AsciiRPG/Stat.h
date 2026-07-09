#pragma once
#include "Component.h"
class Stat : public Component
{
public :
    class StatParameter : public Component::ConstructionParamterBase
    {
    public :
        StatParameter(shared_ptr<Entity> entity, int initHp)
            : Component::ConstructionParamterBase(entity)
            , initHp(initHp) 
        {
        }

        int initHp;
    };

    Stat(int64_t id, const std::string& name, shared_ptr<IConstructionParameter> params);

protected:
    int hp;
    int maxHp;
};

