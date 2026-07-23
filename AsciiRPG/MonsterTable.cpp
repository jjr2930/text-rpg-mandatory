#include <cstdio>
#include <fstream>
#include <stdexcept>

#include "json.hpp"
#include "MonsterTable.h"

SINGLETON_INITIALIZER(MonsterTable)

using json = nlohmann::json;

void MonsterTable::Init()
{
    ifstream stream("MonsterTable.json");
    if(!stream.is_open())
    {
        throw runtime_error("Failed to open MonsterTable.json");
    }

    json j;
    stream >> j;

    if (!j.is_array())
    {
        throw runtime_error("Invalid JSON format: expected an array");
    }

    for (auto& element : j)
    { 
        MonsterData data;
        data.key = element["key"].get<int>();
        data.name = element["name"].get<string>();
        data.displayChar = element["displayChar"].get<string>()[0];
        data.dropTableKey = element["dropTableKey"].get<int>();
        data.minFloor = element["minFloor"].get<int>();
        data.maxFloor = element["maxFloor"].get<int>();
        data.hp = element["hp"].get<float>();
        data.attack = element["attack"].get<float>();
        data.defense = element["defense"].get<float>();
        data.exp = element["exp"].get<int>();
        data.attackDelay = element["attackDelay"].get<double>();
        monsterDataList.push_back(make_shared<MonsterData>(data));
    }
}

shared_ptr<MonsterData> MonsterTable::GetMonsterData(int key) const
{
    for (const auto& data : monsterDataList)
    {
        if (data->key == key)
        {
            return data;
        }
    }

    return nullptr;
}

shared_ptr<MonsterData> MonsterTable::GetMonsterData(char displayChar) const
{
    for (const auto& data : monsterDataList)
    {
        if (data->displayChar == displayChar)
        {
            return data;
        }
    }

    return nullptr;
}

vector<shared_ptr<MonsterData>> MonsterTable::GetMonstersByFloor(int floor) const
{
    vector<shared_ptr<MonsterData>> result;
    for (const auto& data : monsterDataList)
    {
        if (data->minFloor <= floor && floor <= data->maxFloor)
        {
            result.emplace_back(data);
        }
    }
    return result;
}

bool MonsterTable::IsExist(char displayChar) const
{
    for (const auto& data : monsterDataList)
    {
        if (data->displayChar == displayChar)
        {
            return true;
        }
    }   

    return false;
}
