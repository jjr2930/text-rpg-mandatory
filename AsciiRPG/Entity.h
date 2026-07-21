#ifndef ENTITY_H
#define ENTITY_H

#include "ObjectManager.h"
#include "Object.h"
#include "Component.h"
#include "TemplateDeclare.h"

using namespace std;

class IConstructionParameter;

class Entity : public Object
{
public:
    using Object::Object;
    ~Entity();

    template <ComponentType T>
    shared_ptr<T> AddComponent();

    template <ComponentType T>
    shared_ptr<T> AddComponent(std::shared_ptr<IConstructionParameter> params);

    template <ComponentType T>
    bool HasComponent() const;

    template <ComponentType T>
    shared_ptr<T> GetComponent();

    template <ComponentType T>
    void RemoveComponent();

    template <ComponentType T>
    bool TryGetComponent(std::shared_ptr<T>& outComponent);

    //void ReserveDeleteEveryComponents();
    void Update();
private:
    std::vector<std::shared_ptr<Component>> components;
};

#include "Entity.inl"
#endif // !ENTITY_H