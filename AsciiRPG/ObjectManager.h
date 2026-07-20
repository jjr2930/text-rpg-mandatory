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

template<class T>
concept ComponentType = std::derived_from<T, Component>;

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

    template<ComponentType ... T>
    vector<tuple<shared_ptr<T> ...>> GetComponentTupleVector()
    {
        vector<tuple<shared_ptr<T> ...>> result;
        for (const auto& entity : createdEntities)
        {
            auto componentsTuple = make_tuple(entity->template GetComponent<T>() ...);

            const bool allComponentsExist = apply(
                [](const auto&... components)
                {
                    return (... && (components != nullptr));
                },
                componentsTuple
            );

            if (allComponentsExist)
            {
                result.emplace_back(std::move(componentsTuple));
            }
        }
        return result;
    }

    template<ComponentType ... T>
    tuple<shared_ptr<T> ...> GetComponentTuple()
    {
        for (const auto& entity : createdEntities)
        {
            auto componentTuple = make_tuple(entity->template GetComponent<T>() ...);
            const bool allComponentsExist = apply(
                [](const auto&... components)
                {
                    return (... && (components != nullptr));
                },
                componentTuple
            );

            if (allComponentsExist)
            {
                return componentTuple;
            }
        }
        return tuple<shared_ptr<T> ...>();
    }


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

#endif // !OBJECTMANAGER_H