#include "Logger.h"
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
    Logger::LogInfo("Entity destroyed: " + name + " (ID: " + std::to_string(id) + ")");

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

void Entity::OnDestroy()
{
    while (components.size() > 0)
    {
        auto component = components.back();
        component->OnDestroy();
        ObjectManager::GetInstance().DestroyObject(component);
        components.pop_back();
    }
}
