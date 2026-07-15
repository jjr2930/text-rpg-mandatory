#include "AlchemyTable.h"

#include <cassert>

SINGLETON_INITIALIZER(AlchemyTable);

void AlchemyTable::Init()
{
    auto smallPotion = make_shared<AlchemyData>(0, 2);
    smallPotion->AddIngredient(10000, 10);
    smallPotion->AddIngredient(10001, 10);

    alchemyDataList.push_back(smallPotion);
}

shared_ptr<AlchemyData> AlchemyTable::GetAlchemyData(int id)
{
    assert(id >= 0 && id < static_cast<int>(alchemyDataList.size()));
    assert(!alchemyDataList.empty());

    for (auto& data : alchemyDataList)
    {
        if (data->id == id)
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
