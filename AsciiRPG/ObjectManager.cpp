#include "ObjectManager.h"
#include "Object.h"
#include "Entity.h"
#include "Logger.h"
#include <format>

using namespace std;

SINGLETON_INITIALIZER(ObjectManager)

shared_ptr<vector<shared_ptr<Entity>>> ObjectManager::GetAllEntities()
{
    auto result = make_shared<vector<shared_ptr<Entity>>>();
    result->reserve(createdEntities.size());
    for (const auto& entity : createdEntities)
    {
        result->emplace_back(entity);
    }
    return result;
}

shared_ptr<Entity> ObjectManager::CreateEntity()
{
    auto entity = CreateOne<Entity>();
    createdEntities.insert(entity);
    return entity;
}

void ObjectManager::BroadcastEvent(shared_ptr<EventParameter> message)
{
    for (auto& pair : createdObjects)
    {
        pair.second->HandleEvent(message);
    }
}

void ObjectManager::DestroyObject(shared_ptr<Object> object)
{
    createdObjects.erase(object->GetId());
}

void ObjectManager::DestroyEntity(shared_ptr<Entity> entity)
{
    createdEntities.erase(entity);
    this->DestroyObject(entity);
    //entity->ReserveDeleteEveryComponents();
}

void ObjectManager::PrintCurrentState()
{
    Logger::LogInfo(format("ObjectCount {}", createdObjects.size()));

    for (const auto& pair : createdObjects)
    {
        Logger::LogInfo(format("Object ID: {}, Name: {}, useCount : {}", pair.first, pair.second->GetName(), pair.second.use_count()));
    }
}
//
//void ObjectManager::DeleteReservedObjects()
//{
//    vector<shared_ptr<Entity>> entitiesToDelete;
//    entitiesToDelete.reserve(createdEntities.size());
//
//    for (auto& pair : createdEntities)
//    {
//        entitiesToDelete.emplace_back(pair);
//    }
//
//    for (auto& item : entitiesToDelete)
//    {
//        if (item->GetDeleteReserved())
//        {
//            createdObjects.erase(item->GetId());
//            createdEntities.erase(item);
//            Logger::LogInfo(format("Deleted Object ID: {}, Name: {}", item->GetId(), item->GetName()));
//        }
//    }
//
//    vector<shared_ptr<Object>> objectsToDelete;
//    objectsToDelete.reserve(createdObjects.size());
//
//    for (auto& pair : createdObjects)
//    {
//        objectsToDelete.emplace_back(pair.second);
//    }
//
//    for (auto& item : objectsToDelete)
//    {
//        if (item->GetDeleteReserved())
//        {
//            createdObjects.erase(item->GetId());
//            Logger::LogInfo(format("Deleted Object ID: {}, Name: {}", item->GetId(), item->GetName()));
//        }
//    }
//}
