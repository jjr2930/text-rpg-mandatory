#ifndef DRAGON_H
#define DRAGON_H

#include "Component.h"

#include <memory>

using namespace std;

class Stat;
class Position;

class Dragon : public Component
{
public:
    using Component::Component;
    Dragon(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);


private:
    shared_ptr<Stat> stat;
    shared_ptr<Position> position;
};

#endif