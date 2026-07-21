#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <unordered_map>
#include <random>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <tuple>

#include "TemplateDeclare.h"
#include "SingletonMacro.h"
#include "Object.h"
#include "Random.h"
#include "Component.h"

using namespace std;

class EventParameter;
class IConstructionParameter;
class Entity;
class VirtualDisplay;

class ObjectManager
{
    SINGLETON(ObjectManager)

public:

    template <ObjectType T>
    shared_ptr<T> CreateOne();

    template <ObjectType T>
    shared_ptr<T> CreateOne(shared_ptr<IConstructionParameter> params);

    template <ObjectType T>
    vector<shared_ptr<T>> GetObjectsByType();

    template<ObjectType T>
    shared_ptr<T> GetObjectByType();

    template<ComponentType ... T>
    vector<tuple<shared_ptr<T> ...>> GetComponentTupleVector();

    template<ComponentType ... T>
    tuple<shared_ptr<T> ...> GetComponentTuple();

    /// <summary>
    /// 이거 왜케 더러워
    /// </summary>
    /// <returns></returns>
    shared_ptr<vector<shared_ptr<Entity>>> GetAllEntities();

    shared_ptr<Entity> CreateEntity();

    void BroadcastEvent(shared_ptr<EventParameter> message);    
    void DestroyObject(shared_ptr<Object> object);
    void DestroyEntity(shared_ptr<Entity> entity);
    void PrintCurrentState();
    //void DeleteReservedObjects();

private:
    unordered_map<int64_t, shared_ptr<Object>> createdObjects;
    unordered_set<shared_ptr<Entity>> createdEntities;
};

#include "ObjectManager.inl"

#endif // !OBJECTMANAGER_H