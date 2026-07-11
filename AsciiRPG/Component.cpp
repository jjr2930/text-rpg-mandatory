#include "Component.h"
#include "Entity.h"
#include "Logger.h"

#include <memory>

using namespace std;

Component::Component(int64_t id, const std::string& name, shared_ptr<IConstructionParameter> params)
    :Object(id, name)
{
    auto constructionParams = static_cast<Component::ConstructionParamterBase*>(params.get());
    
    entity = constructionParams->entity;
}

Component::~Component()
{
    //Logger::LogInfo("Component destroyed: " + name + " (ID: " + std::to_string(id) + ")");
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
    return entity.lock();
}

void Component::DestroyEntity()
{
    if (auto ptr = entity.lock())
    {
        ObjectManager::GetInstance().DestroyEntity(ptr);
    }
}

Component::ConstructionParamterBase::ConstructionParamterBase(shared_ptr<Entity> entity)
{
    this->entity = entity;
}
