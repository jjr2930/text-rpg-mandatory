#include "ItemBank.h"
#include "ConsumableItemTable.h"
#include "IngredientTable.h"
#include "Random.h"

SINGLETON_INITIALIZER(ItemBank)

shared_ptr<IItem> ItemBank::GetItem(int tableKey, ItemType type) const
{
    switch (type)
    {
        case ItemType::None:
            break;
        case ItemType::Consumable:
            return ConsumableItemTable::GetInstance().GetData(tableKey);
        case ItemType::Ingredient:
            return IngredientTable::GetInstance().GetData(tableKey);
        default:
            break;
    }
    return nullptr;
}

string ItemBank::GetName(int tableKey, ItemType type) const
{
    switch (type)
    {
        case ItemType::None:
            break;
        case ItemType::Consumable:
            return ConsumableItemTable::GetInstance().GetData(tableKey)->name;
        case ItemType::Ingredient:
            return IngredientTable::GetInstance().GetData(tableKey)->name;
        default:
            break;
    }
    return "";
}

shared_ptr<IItem> ItemBank::GetRandomItem() const
{
    ItemType randomType = (ItemType)Random::GetInstance().RandomRange((int)ItemType::Consumable, (int)ItemType::Ingredient);
    
    switch (randomType)
    {
        case ItemType::Consumable:
            return ConsumableItemTable::GetInstance().GetRandomItem();
        
        case ItemType::Ingredient:
            return IngredientTable::GetInstance().GetRandomItem();

        default:
            throw runtime_error(format("Not supported itemType, {}", static_cast<int>(randomType)));
    }
}
