#include "ItemTable.h"

SINGLETON_INITIALIZER(ItemTable)

const ItemData* ItemTable::GetItemData(int id) const
{
    auto it = rows.find(id);
    if (it != rows.end())
    {
        return &it->second;
    }
    return nullptr;
}

void ItemTable::Init()
{
    //key,      key, name,       cost,   useable,    statType,                      operatorType,           amount, isInstant, duration, interv
    rows[1] = { 1, "Gold",         10,     false,      StatType::None,              OperatorType::None,     0.0f,   false,      0.0,        0.0 };
    rows[2] = { 2, "Small Potion", 20,     true,       StatType::CurrentHealth,     OperatorType::Add,      10.0f,  true,       0.0,        0.0 };
}
