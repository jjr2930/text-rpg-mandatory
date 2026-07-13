#include "Logger.h"
#include "Entity.h"
#include "Component.h"

#include <format>

//Entity::Entity(int64_t id, const std::string& name)
//: Object(id, name)
//{}
//
//Entity::Entity(int64_t id, const std::string & name, std::vector<std::shared_ptr<IConstructionParameter>>&params)
//: Object(id, name)
//{}

Entity::~Entity()
{
    //Logger::LogInfo(format("Entity Destructor called for Entity ID: {}, Name: {}", GetId(), GetName()));
    while (components.size() > 0)
    {
        auto component = components.back();

        ObjectManager::GetInstance().DestroyObject(component);

        components.pop_back();
    }
}

//void Entity::ReserveDeleteEveryComponents()
//{
//    for (auto& com : components)
//    {
//        ObjectManager::GetInstance().DestroyObject(com);
//    }
//}

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
