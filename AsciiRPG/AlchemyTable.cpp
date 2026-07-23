#include "AlchemyTable.h"
#include "json.hpp"
#include "Const.h"

#include <cassert>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

SINGLETON_INITIALIZER(AlchemyTable);

void AlchemyTable::Init()
{
    std::ifstream fileStream("AlchemyTable.json");
    if (!fileStream.is_open() )
    {
        throw std::runtime_error("Failed to open AlchemyTable.json");
    }
    json alchemyJson;
    fileStream >> alchemyJson;

    if (!alchemyJson.is_array())
    {
        throw std::runtime_error("AlchemyTable.json is not array");
    }

    for (auto& iter : alchemyJson)
    {
        AlchemyData newData;
        newData.key = iter["key"].get<int>();
        newData.resultItemKey = iter["resultKey"].get<int>();

        if (Const::Items::NonConsumableItemKeys.contains(newData.resultItemKey))
            continue;

        for (auto& ingredient : iter["ingredients"])
        {
            AlchemyDataElement element;
            element.itemKey = ingredient["key"].get<int>();
            element.quantity = ingredient["quantity"].get<int>();
            newData.ingredients.push_back(element);
        }
        alchemyDataList.emplace_back(make_shared<AlchemyData>(newData));
    }
}

shared_ptr<AlchemyData> AlchemyTable::GetAlchemyData(int id)
{
    assert(id >= 0 && id < static_cast<int>(alchemyDataList.size()));
    assert(!alchemyDataList.empty());

    for (auto& data : alchemyDataList)
    {
        if (data->key == id)
        {
            return data;
        }
    }

    return nullptr;
}

vector<shared_ptr<AlchemyData>>& AlchemyTable::GetAllAlchemyData()
{
    return alchemyDataList;
}
