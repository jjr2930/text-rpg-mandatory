#ifndef ENTITY_H
#define ENTITY_H

#include "ObjectManager.h"
#include "Object.h"

using namespace std;

class IConstructionParameter;
class Component;

class Entity : public Object
{
public:
    using Object::Object;
    ~Entity();

    template <typename T,
        typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
    shared_ptr<T> AddComponent()
    {
        auto component = ObjectManager::GetInstance().CreateOne<T>();
        components.push_back(component);
        return component;
    }

    template <typename T,
        typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
    shared_ptr<T> AddComponent(std::shared_ptr<IConstructionParameter> params)
    {
        auto component = ObjectManager::GetInstance().CreateOne<T>(params);
        components.push_back(component);
        return component;
    }

    template <typename T,
        typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
    bool HasComponent() const
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

    template <typename T,
        typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
    shared_ptr<T> GetComponent()
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

    template <typename T,
        typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
    void RemoveComponent()
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

    template <typename T,
        typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
    bool TryGetComponent(std::shared_ptr<T>& outComponent)
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

    //void ReserveDeleteEveryComponents();
    void Update();
private:
    std::vector<std::shared_ptr<Component>> components;
};


#endif // !ENTITY_H