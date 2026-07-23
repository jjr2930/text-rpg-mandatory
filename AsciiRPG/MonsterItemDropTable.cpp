#include <cstdio>
#include <fstream>

#include "MonsterItemDropTable.h"
#include "json.hpp"

SINGLETON_INITIALIZER(MonsterItemDropTable)

const vector<shared_ptr<MonsterItemDropData>>& MonsterItemDropTable::GetDropItems(int dropGroupKey) const
{
    for (const auto& group : dropGroups)
    {
        if (group.key == dropGroupKey)
        {
            return group.dropItems;
        }
    }

    static vector<shared_ptr<MonsterItemDropData>> emptyVector;
    return emptyVector;
}

void MonsterItemDropTable::Init()
{
    //TODO: filename change to MonsterDropItemTable.json
    ifstream fileInputStream("MonsterItemDropTable.json");
    if (!fileInputStream.is_open())
    {
        throw runtime_error("Failed to open MonsterItemDropTable.json");
    }

    nlohmann::json jsonData;
    fileInputStream >> jsonData;
    if (!jsonData.is_array())
    {
        throw runtime_error("Invalid JSON format: Expected an array of drop groups.");
    }

    // Process jsonData to initialize dropGroups
    for (auto& element : jsonData)
    {
        MonsterItemDropGroup dropGroup;
        dropGroup.key= element["key"].get<int>();
        dropGroup.name = element["name"].get<string>();
        for (auto& item : element["dropItems"])
        {
            shared_ptr<MonsterItemDropData> dropItem = make_shared<MonsterItemDropData>();
            dropItem->key = item["key"].get<int>();
            dropItem->minQuantity = item["minQuantity"].get<int>();
            dropItem->maxQuantity = item["maxQuantity"].get<int>();
            dropItem->dropChance = item["dropChance"].get<double>();
            dropGroup.dropItems.emplace_back(dropItem);
        }
        dropGroups.emplace_back(dropGroup);
    }
}
