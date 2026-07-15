#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>

struct ItemData;

using namespace std;

class InventoryItem
{
public:
    InventoryItem(int tableKey, int quantity)
        : tableKey(tableKey)
        , quantity(quantity)
    {
    }
    //setter or kindof setter
    int AddQuantity(int amount);
    int SetQuantity(int amount);

    //getter
    int GetTableKey() const; 
    int GetQuantity() const; 
    string GetName() const;
    bool GetIsUsable() const;
    const ItemData* GetItemDataFromTable() const;
    
private:
    int tableKey;
    int quantity;
};

#endif
