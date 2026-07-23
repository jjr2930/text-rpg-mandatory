#ifndef ITEM_BANK_H
#define ITEM_BANK_H

#include "Enums.h"
#include "SingletonMacro.h"

#include <memory>
#include <string>

class IItem;

using namespace std;

class ItemBank
{
public:
    SINGLETON(ItemBank);

public:
    shared_ptr<IItem> GetItem(int tableKey, ItemType type ) const;
    string GetName(int tableKey, ItemType type) const;
    shared_ptr<IItem> GetRandomItem() const;
};

#endif // !ITEM_BANK_H