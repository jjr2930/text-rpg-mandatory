#ifndef DUNGEON_OBJECT_TAG
#define DUNGEON_OBJECT_TAG

#include "Component.h"
#include "IConstructionParameter.h"

class DungeonObjectTag : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, char tag)
            : Component::ConstructionParamterBase(entity)
            , tag(tag)
        {}

        char tag;
    };

public:
    using Component::Component;
    DungeonObjectTag(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    char GetTag() const { return tag; }

private:
    char tag;
};

#endif // !DUNGEON_OBJECT_TAG