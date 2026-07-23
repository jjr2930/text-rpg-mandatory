#include "AlchemyData.h"
#include "ConsumableItemTable.h"
#include "ItemBank.h"

#include <format>

vector<string> AlchemyData::GetRenderString() const
{
    vector<string> result;
    auto resultItemData = ConsumableItemTable::GetInstance().GetData(resultItemKey);
    result.emplace_back(resultItemData->name);

    for (const auto& ingredient : ingredients)
    {
        string ingredientName = ItemBank::GetInstance().GetName(ingredient.itemKey, ItemType::Ingredient);

        result.emplace_back(format(" - {} x {}", ingredientName, ingredient.quantity));
    }

    return result;
}
