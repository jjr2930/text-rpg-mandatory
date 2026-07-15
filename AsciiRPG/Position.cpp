#include "Position.h"
#include "ObjectManager.h"
#include "Entity.h"
#include "Wall.h"
#include "Monster.h"
#include "Npc.h"
#include "InteractableObject.h"

Position::Position(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    auto constructParam = static_cast<ConstructParameter*>(params.get());

    x = constructParam->x;
    y = constructParam->y;
}

void Position::TryMoveXOnly(int deltaX)
{
    //상당히 비요율 적이군...

    auto positions = ObjectManager::GetInstance().GetObjectsByType<Position>();
    for (auto otherPosition : positions)
    {
        if (otherPosition->GetId() == this->GetId())
        {
            continue;
        }

        if (CanMoveTo(otherPosition, this->GetX() + deltaX, this->GetY()) == false)
        {
            return;
        }
    }

    //can move
    this->AddX(deltaX);
}


void Position::TryMoveYOnly(int deltaY)
{
    auto positions = ObjectManager::GetInstance().GetObjectsByType<Position>();
    for (auto position : positions)
    {
        string entityName = position->GetEntity()->GetName();
        if (position->GetId() == this->GetId())
        {
            continue;
        }

        if (CanMoveTo(position, this->GetX(), this->GetY() + deltaY) == false)
        {
            return;
        }
    }

    //can move
    this->AddY(deltaY);
}

bool Position::CanMoveTo(shared_ptr<Position> position, int newX, int newY)
{
    if (position->GetX() == newX && position->GetY() == newY)
    {
        weak_ptr<Entity> entityWeakPtr = position->entity;  
        if (auto entityPtr = entityWeakPtr.lock())
        {
            if (entityPtr->HasComponent<Wall>())
            {
                return false;
            }

            if (entityPtr->HasComponent<Monster>())
            {
                return false;
            }

            if(entityPtr->HasComponent<InteractableObject>())
            {
                return false;
            }
        }
    }

    return true;
}