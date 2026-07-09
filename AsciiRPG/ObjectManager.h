#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "SingletonMacro.h"

#include <unordered_map>
#include <random>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>
#include <tuple>

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

    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    shared_ptr<T> CreateOne()
    {
        int64_t randomNumber = Random::GetInstance().RandomRange(INT64_MIN, INT64_MAX);
        shared_ptr<T> newOne = make_shared<T>(randomNumber, string());
        createdObjects.insert({ randomNumber, newOne });

        return newOne;
    }

    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    shared_ptr<T> CreateOne(shared_ptr<IConstructionParameter> params)
    {
        int64_t randomNumber = Random::GetInstance().RandomRange(INT64_MIN, INT64_MAX);
        shared_ptr<T> newOne = make_shared<T>(randomNumber, string(), params);
        createdObjects.insert({ randomNumber, newOne });

        return newOne;
    }
    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    vector<shared_ptr<T>> GetObjectsByType() 
    {
        vector<shared_ptr<T>> result;

        for (const auto& pair : createdObjects)
        {
            if (auto castedObject = dynamic_pointer_cast<T>(pair.second))
            {
                result.push_back(castedObject);
            }
        }

        return result;
    }

    template <typename T,
        typename = enable_if_t<is_base_of<Object, T>::value>>
    shared_ptr<T> GetObjectByType()
    {
        for (const auto& pair : createdObjects)
        {
            if (auto castedObject = dynamic_pointer_cast<T>(pair.second))
            {
                return castedObject;
            }
        }

        return nullptr;
    }

    template <typename T1, typename T2,
        typename = enable_if_t<is_base_of<Component, T1>::value>,
        typename = enable_if_t<is_base_of<Component, T2>::value>>
    vector<tuple<shared_ptr<T1>, shared_ptr<T2>>> GetComponentsWithTypes()
    {
        vector<tuple<shared_ptr<T1>, shared_ptr<T2>>> result;
        for (const auto& entity : createdEntities)
        {
            auto component1 = entity->template GetComponent<T1>();
            auto component2 = entity->template GetComponent<T2>();
            if (component1 && component2)
            {
                result.emplace_back(component1, component2);
            }
        }
        return result;
    }

    shared_ptr<Entity> CreateEntity();


    void BroadCastMessage(shared_ptr<EventParameter> message);    
    void DestroyObject(shared_ptr<Object> object);
    void DestroyEntity(shared_ptr<Entity> entity);

private:
    void Init();
private:
    unordered_map<int64_t, shared_ptr<Object>> createdObjects;
    unordered_set<shared_ptr<Entity>> createdEntities;
};

#endif // !OBJECTMANAGER_H