#include "DungeonObjectTag.h"

DungeonObjectTag::DungeonObjectTag(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    auto constructionParams = std::static_pointer_cast<ConstructionParameter>(params);

    tag = constructionParams->tag;
}