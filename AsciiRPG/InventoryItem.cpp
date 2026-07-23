#include "InventoryItem.h"
#include "IngredientTable.h"
#include "ItemBank.h"

#include <cassert>

int InventoryItem::GetTableKey() const
{
    return tableKey;
}

int InventoryItem::GetQuantity() const
{
    return quantity;
}

int InventoryItem::AddQuantity(int amount)
{
    quantity += amount;
    return quantity;
}

int InventoryItem::SetQuantity(int amount)
{
    quantity = amount;
    return quantity;
}

string InventoryItem::GetName() const
{
    //TODO: 느려!
    return ItemBank::GetInstance().GetName(tableKey, itemType);
}

bool InventoryItem::GetIsUsable() const
{
    const auto foundItem = ItemBank::GetInstance().GetItem(tableKey, itemType);
    
    assert(foundItem && "Item data not found");

    return foundItem->isUsable;
}

const shared_ptr<IItem> InventoryItem::GetItemDataFromTable() const
{
    return ItemBank::GetInstance().GetItem(tableKey, itemType);
}
