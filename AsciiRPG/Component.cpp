#include "Component.h"
#include <memory>

using namespace std;

Component::Component(int64_t id, const std::string& name, shared_ptr<IConstructionParameter> params)
    :Object(id, name)
{
    auto constructionParams = static_cast<Component::ConstructionParamterBase*>(params.get());
    
    entity = constructionParams->entity;
}

bool Component::GetIsStarted() const
{
    return isStarted;
}

void Component::SetIsStarted(bool value)
{
    isStarted = value;
}

shared_ptr<Entity> Component::GetEntity() const
{
    return entity;
}
