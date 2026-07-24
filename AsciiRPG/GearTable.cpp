#include "GearTable.h"
#include "json.hpp"
#include "Random.h"

#include <fstream>

using json = nlohmann::json;

SINGLETON_INITIALIZER(GearTable)

shared_ptr<GearData> GearTable::GetData(int key) const
{
    auto iter = gearDataMap.find(key);
    assert(iter != gearDataMap.end() && "Gear data not found for the given key.");

    return iter->second;
}

shared_ptr<IItem> GearTable::GetRandomItem() const
{
    auto size = gearDataMap.size();
    int randomNumber = Random::GetInstance().RandomRange(0, static_cast<int>(size) - 1);

    auto iter = gearDataMap.begin();
    std::advance(iter, randomNumber);

    return iter->second;
}

unordered_map<int, shared_ptr<GearData>> GearTable::GetAllData()
{
    return gearDataMap;
}

void GearTable::Init()
{
    ifstream file("GearTable.json");
    json j;
    file >> j;

    if (!j.is_array())
    {
        throw runtime_error("Invalid JSON format: expected an array of gear data.");
    }
    
    for (const auto& item : j)
    {
        auto gearData = make_shared<GearData>();
        gearData->itemType = ItemType::Gear;
        gearData->key = item["key"].get<int>();
        gearData->name = item["name"].get<string>();
        gearData->isUsable = item["isUsable"].get<bool>();
        gearData->cost = item["cost"].get<int>();
        gearData->slot = item["slot"].get<GearSlotType>();
        gearData->minLevel = item["minLevel"].get<int>();
        for (const auto& modifier : item["statModifiers"])
        {
            auto statModifier = make_shared<GearStatModifier>();
            statModifier->statType = modifier["statType"].get<StatType>();
            statModifier->operatorType = modifier["operatorType"].get<OperatorType>();
            statModifier->amount = modifier["amount"].get<float>();
            gearData->statModifiers.emplace_back(statModifier);
        }
        gearDataMap[gearData->key] = gearData;
    }
}
