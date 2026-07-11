#include "FieldItem.h"
#include "ObjectManager.h"
#include "Position.h"
#include "Player.h"
#include "MathUtility.h"
#include "Entity.h"

#include <memory>

FieldItem::FieldItem(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    :Component(id, name, params)
{
    auto constructionParams = static_cast<ConstructionParameter*>(params.get());

    itemName = constructionParams->itemName;
    quantity = constructionParams->quantity;
        
    if(auto ptr = entity.lock())
        myPosition = ptr->GetComponent<Position>();
}

string FieldItem::GetItemName() const
{
    return itemName;
}

int FieldItem::GetQuantity() const
{
    return quantity;
}

void FieldItem::Update()
{
    auto players = ObjectManager::GetInstance().GetComponentsWithTypes<Player, Position>();
    //i need only one
    auto& [player, position] = players[0];

    if(MathUtility::IsOverlap(myPosition->GetPosition(), position->GetPosition(), 0))
    {
        player->AddItem(*this);

        DestroyEntity();
    }
}

void FieldItem::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnMapClearRequested:
            if (auto entityPtr = entity.lock())
            {
                ObjectManager::GetInstance().DestroyEntity(entityPtr);
            }
            break;
        default:
            break;
    }
}
