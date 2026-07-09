#include "ObjectManager.h"
#include "Object.h"
#include "Entity.h"
#include "Logger.h"
#include <format>

using namespace std;

SINGLETON_INITIALIZER(ObjectManager)

shared_ptr<Entity> ObjectManager::CreateEntity()
{
    auto entity = CreateOne<Entity>();
    createdEntities.insert(entity);
    return entity;
}

void ObjectManager::BroadCastMessage(shared_ptr<EventParameter> message)
{
    for (auto& pair : createdObjects)
    {
        pair.second->HandleEvent(message);
    }
}

void ObjectManager::DestroyObject(shared_ptr<Object> object)
{
    this->createdObjects.erase(object->GetId());
}

void ObjectManager::DestroyEntity(shared_ptr<Entity> entity)
{
    entity->OnDestroy();
    this->DestroyObject(entity);
    this->createdEntities.erase(entity);
}

void ObjectManager::Init()
{
}
