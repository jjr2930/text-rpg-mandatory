#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>

using namespace std;

class InventoryItem
{
public:
    InventoryItem(const string& name, int quantity)
        : name(name)
        , quantity(quantity)
    {
    }

    //getter
    const string& GetName() const { return name; }
    int GetQuantity() const { return quantity; }

private:
    string name;
    int quantity;
};

#endif
