#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include "Enums.h"

#include <string>
#include <memory>

class IItem;

using namespace std;

class InventoryItem
{
public:
    InventoryItem(int tableKey, ItemType itemType, int quantity)
        : tableKey(tableKey)
        , itemType(itemType)
        , quantity(quantity)
    {
    }
    //setter or kindof setter
    int AddQuantity(int amount);
    int SetQuantity(int amount);

    //getter
    int GetTableKey() const; 
    ItemType GetItemType() const;
    int GetQuantity() const; 
    string GetName() const;
    bool GetIsUsable() const;
    const shared_ptr<IItem> GetItemDataFromTable() const;
    
private:
    int tableKey;
    ItemType itemType;
    int quantity;
};

#endif
