#include "InventoryItem.h"
#include "ItemTable.h"
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

string InventoryItem::GetName() const
{
    //TODO: 느려!
    const ItemData* itemData = ItemTable::GetInstance().GetItemData(tableKey);
    
    assert(itemData && "Item data not found");

    return itemData->name;
}

bool InventoryItem::GetIsUsable() const
{
    const ItemData* itemData = ItemTable::GetInstance().GetItemData(tableKey);
    
    assert(itemData && "Item data not found");

    return itemData->isUsable;
}

const ItemData* InventoryItem::GetItemDataFromTable() const
{
    const ItemData* itemData = ItemTable::GetInstance().GetItemData(tableKey);
    
    assert(itemData && "Item data not found");

    return itemData;
}
