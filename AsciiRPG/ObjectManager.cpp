#include "ObjectManager.h"
#include "Object.h"
#include "Entity.h"

SINGLETON_INITIALIZER(ObjectManager)

shared_ptr<Entity> ObjectManager::CreateEntity()
{
    auto entity = CreateOne<Entity>();
    createdEntities.insert(entity);
    return entity;
}

void ObjectManager::DestroyObject(shared_ptr<Object> object)
{
    this->createdObjects.erase(object->GetId());

    if (auto entity = dynamic_pointer_cast<Entity>(object))
    {
        this->createdEntities.erase(entity);
    }
}

void ObjectManager::DestroyEntity(shared_ptr<Entity> entity)
{
    this->createdEntities.erase(entity);
}

void ObjectManager::Init()
{
}
