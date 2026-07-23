#include "Logger.h"
#include "Entity.h"
#include "Component.h"
#include "Enums.h"

#include <format>

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
