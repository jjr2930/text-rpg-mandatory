#ifndef ITEM_TABLE_H
#define ITEM_TABLE_H

#include "Enums.h"
#include "SingletonMacro.h"
#include "ItemData.h"

#include <string>
#include <unordered_map>

using namespace std;


class ItemTable
{
public:
    SINGLETON_WITH_INIT(ItemTable)

public:
    const ItemData* GetItemData(int id) const;
    const string GetItemName(int id) const;

    void Init();

private:
    unordered_map<int, ItemData> rows;

};
#endif // !ITEM_TABLE_H