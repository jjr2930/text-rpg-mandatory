#ifndef NPC_H   
#define NPC_H

#include "Component.h"

#include <memory>

using namespace std;

class Position;

class Npc : public Component
{
public:
    using Component::Component;
    Npc(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    void Update() override;

protected:
    shared_ptr<Position> npcPosition;
    uint64_t lastOverlapEntityId;
};

#endif // NPC_H
