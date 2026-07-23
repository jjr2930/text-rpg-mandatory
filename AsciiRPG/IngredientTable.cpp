#include <fstream>

#include "IngredientTable.h"
#include "json.hpp"
#include "Random.h"

using json = nlohmann::json;

SINGLETON_INITIALIZER(IngredientTable)

shared_ptr<IngredientData> IngredientTable::GetData(int key) const
{
    for (const auto& ingredientData : ingredientDataList)
    {
        if (ingredientData->key == key)
        {
            return ingredientData;
        }
    }
    return nullptr; 
}

shared_ptr<IItem> IngredientTable::GetRandomItem() const
{
    auto size = (int)ingredientDataList.size();
    if (size == 0)
        return nullptr;

    int randomIndex = Random::GetInstance().RandomRange(0, size - 1);
    return ingredientDataList[randomIndex];
}

void IngredientTable::Init()
{
    ifstream fileInputStream("IngredientTable.json");
    if (!fileInputStream.is_open())
        throw runtime_error("Failed to open IngredientTable.json");

    json jsonData;
    fileInputStream >> jsonData;

    for (const auto& item : jsonData)
    {
        auto ingredientData = make_shared<IngredientData>();
        ingredientData->key = item["key"];
        ingredientData->name = item["name"];
        ingredientData->isUsable = false;
        ingredientData->cost = item["cost"];
        ingredientDataList.emplace_back(ingredientData);
    }
}

IngredientData::IngredientData()
{
    itemType = ItemType::Ingredient;
}
