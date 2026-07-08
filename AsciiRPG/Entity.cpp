
#include "Entity.h"
#include "Component.h"
//Entity::Entity(int64_t id, const std::string& name)
//: Object(id, name)
//{}
//
//Entity::Entity(int64_t id, const std::string & name, std::vector<std::shared_ptr<IConstructionParameter>>&params)
//: Object(id, name)
//{}

Entity::~Entity()
{
    while (components.size() > 0)
    {
        auto component = components.back();
        component->OnDestroy();
        ObjectManager::GetInstance().DestroyObject(component);
        components.pop_back();
    }
}

void Entity::Update()
{
    for (auto& component : components)
    {
        if (!component->GetIsStarted())
        {
            component->Start();
            component->SetIsStarted(true);
        }
        component->Update();
    }
}
