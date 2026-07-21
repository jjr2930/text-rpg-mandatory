#ifndef OBJECTMANAGER_INL
#define OBJECTMANAGER_INL

#include "Object.h"
#include "Entity.h"
#include "ObjectManager.h"


template <ObjectType T>
shared_ptr<T> ObjectManager::CreateOne()
{
    int64_t randomNumber = Random::GetInstance().RandomRange(INT64_MIN, INT64_MAX);
    shared_ptr<T> newOne = make_shared<T>(randomNumber, string());
    createdObjects.insert({ randomNumber, newOne });

    return newOne;
}

template <ObjectType T>
shared_ptr<T> ObjectManager::CreateOne(shared_ptr<IConstructionParameter> params)
{
    int64_t randomNumber = Random::GetInstance().RandomRange(INT64_MIN, INT64_MAX);
    shared_ptr<T> newOne = make_shared<T>(randomNumber, string(), params);
    createdObjects.insert({ randomNumber, newOne });

    return newOne;
}
template <ObjectType T>
vector<shared_ptr<T>> ObjectManager::GetObjectsByType() 
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

template<ObjectType T>
shared_ptr<T> ObjectManager::GetObjectByType()
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
vector<tuple<shared_ptr<T> ...>> ObjectManager::GetComponentTupleVector()
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
tuple<shared_ptr<T> ...> ObjectManager::GetComponentTuple()
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

#endif // !OBJECTMANAGER_INL
