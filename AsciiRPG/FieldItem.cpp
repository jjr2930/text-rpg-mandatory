#include "FieldItem.h"
#include "ObjectManager.h"
#include "Position.h"
#include "Player.h"
#include "MathUtility.h"
#include "Entity.h"
#include "ItemBank.h"

#include <memory>
#include <cassert>

FieldItem::FieldItem(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    :Component(id, name, params)
{
    auto constructionParams = static_cast<ConstructionParameter*>(params.get());

    tableKey = constructionParams->tableKey;
    itemType = constructionParams->itemType;
    quantity = constructionParams->quantity;
        
    if(auto ptr = entity.lock())
        myPosition = ptr->GetComponent<Position>();
}

string FieldItem::GetName() const
{
    return ItemBank::GetInstance().GetName(tableKey, itemType);
}

int FieldItem::GetTableKey() const
{
    return tableKey;    
}

int FieldItem::GetQuantity() const
{
    return quantity;
}

ItemType FieldItem::GetItemType() const
{
    return itemType;
}

void FieldItem::Update()
{
    auto [player, position] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();

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
