#include "AlchemyData.h"
#include "ItemTable.h"
#include "ItemData.h"

#include <format>

AlchemyData::AlchemyData(int id, int resultItemKey)
    : id(id), resultItemKey(resultItemKey)
{}

void AlchemyData::AddIngredient(int itemKey, int quantity)
{
    ingredients.push_back({ itemKey, quantity });
}

vector<string> AlchemyData::GetRenderString() const
{
    vector<string> result;
    auto resultItemData = ItemTable::GetInstance().GetItemData(resultItemKey);
    result.emplace_back(resultItemData->name);

    for (const auto& ingredient : ingredients)
    {
        string ingredientName = ItemTable::GetInstance().GetItemName(ingredient.itemKey);
        result.emplace_back(format(" - {} x {}", ingredientName, ingredient.quantity));
    }

    return result;
}
