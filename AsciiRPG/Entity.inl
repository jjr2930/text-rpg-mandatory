#ifndef ENTITY_INL
#define ENTITY_INL

#include <memory>

#include "Entity.h"
#include "ObjectManager.h"

using namespace std;

template <ComponentType T>
shared_ptr<T> Entity::AddComponent()
{
    auto component = ObjectManager::GetInstance().CreateOne<T>();
    components.push_back(component);
    return component;
}

/// <summary>
/// TODO: params do not use shared_ptr, use reference or value copy, because make_shared hide constructor's parameter infomation...
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="params"></param>
/// <returns></returns>
template <ComponentType T>
shared_ptr<T> Entity::AddComponent(std::shared_ptr<IConstructionParameter> params)
{
    auto component = ObjectManager::GetInstance().CreateOne<T>(params);
    components.push_back(component);
    return component;
}


template <ComponentType T>
bool Entity::HasComponent() const
{
    for (const auto& component : components)
    {
        if (std::dynamic_pointer_cast<T>(component))
        {
            return true;
        }
    }
    return false;
}

template <ComponentType T>
shared_ptr<T> Entity::GetComponent()
{
    for (const auto& component : components)
    {
        if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
        {
            return castedComponent;
        }
    }
    return nullptr;

}

template <ComponentType T>
void Entity::RemoveComponent()
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        if (std::dynamic_pointer_cast<T>(*it))
        {
            auto oldComponent = *it;
            ObjectManager::GetInstance().DestroyObject(oldComponent);
            components.erase(it);
            return;
        }
    }
}

template <ComponentType T>
bool Entity::TryGetComponent(std::shared_ptr<T>& outComponent)
{
    for (const auto& component : components)
    {
        if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
        {
            outComponent = castedComponent;
            return true;
        }
    }
    return false;
}

#endif // !ENTITY_INL

