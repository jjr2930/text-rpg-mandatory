#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>

class ItemData;

using namespace std;

class InventoryItem
{
public:
    InventoryItem(int tableKey, int quantity)
        : tableKey(tableKey)
        , quantity(quantity)
    {
    }

    //getter
    int GetTableKey() const; 
    int GetQuantity() const; 
    int AddQuantity(int amount);
    string GetName() const;
    bool GetIsUsable() const;
    const ItemData* GetItemDataFromTable() const;
    
private:
    int tableKey;
    int quantity;
};

#endif
