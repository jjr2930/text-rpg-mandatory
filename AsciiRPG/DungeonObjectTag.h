#ifndef DUNGEON_OBJECT_TAG
#define DUNGEON_OBJECT_TAG

#include "Component.h"
#include "IConstructionParameter.h"
#include "Enums.h"

/// <summary>
/// TODO: StaticObjectTag
/// </summary>
class DungeonObjectTag : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, DungeonTagTypes tag)
            : Component::ConstructionParamterBase(entity)
            , tag(tag)
        {}

        DungeonTagTypes tag;
    };

public:
    using Component::Component;
    DungeonObjectTag(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    DungeonTagTypes GetTag() const { return tag; }

private:
    DungeonTagTypes tag;
};

#endif // !DUNGEON_OBJECT_TAG