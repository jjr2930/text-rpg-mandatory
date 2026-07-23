//#include "Enums.h"
#include <fstream>
#include <cstdio>

#include "Logger.h"
#include "ConsumableItemTable.h"
#include "json.hpp"
#include "Random.h"

using json = nlohmann::json;

SINGLETON_INITIALIZER(ConsumableItemTable)

const shared_ptr<ConsumableItemData> ConsumableItemTable::GetData(int id) const
{
    auto it = data.find(id);
    if (it != data.end())
    {
        return it->second;
    }
    return nullptr;
}

const string ConsumableItemTable::GetItemName(int id) const
{
    auto itemData = GetData(id);
    if (itemData)
    {
        return itemData->name;
    }   

    return string();
}

shared_ptr<IItem> ConsumableItemTable::GetRandomItem() const
{
    int size = static_cast<int>(data.size());
    //TODO: ingredient table also change to assert 
    assert(size > 0 && "ConsumableItemTable is empty, cannot get random item");


    int randomIndex = Random::GetInstance().RandomRange(0, size - 1);
    auto it = data.begin();
    std::advance(it, randomIndex);

    return it->second;
}

void ConsumableItemTable::Init()
{
    string jsonFilePath = std::filesystem::current_path().string();
    std::ifstream i("ConsumableItemTable.json");
    if (!i.is_open())
    {
        throw std::runtime_error("Failed to open ConsumableItemTable.json");
    }

    json consumableItemTableJson = json::parse(i);

    if (!consumableItemTableJson.is_array())
    {
        throw std::runtime_error("ConsumableItemTable root must be an array");
    }

    for (auto& iter : consumableItemTableJson)
    {
        shared_ptr<ConsumableItemData> newItemData = make_shared<ConsumableItemData>();
        newItemData->key = iter["key"].get<int>();
        if (Const::Items::NonConsumableItemKeys.contains(newItemData->key))
            continue;

        newItemData->name = iter["name"].get<std::string>(); 
        newItemData->cost = iter["cost"].get<int>();
        newItemData->isUsable= iter["isUsable"].get<bool>();
        newItemData->statType = iter["statType"].get<StatType>();
        newItemData->operatorType = iter["operatorType"].get<OperatorType>();
        newItemData->amount = iter["amount"].get<float>();
        newItemData->isInstant = iter["isInstant"].get<bool>();
        newItemData->duration = iter["duration"].get<double>();
        newItemData->interval = iter["interval"].get<double>();

        data[newItemData->key] = newItemData;
    }
}

ConsumableItemData::ConsumableItemData()
{
    itemType = ItemType::Consumable;
}
