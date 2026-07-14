#include "AlchemyTable.h"

#include <cassert>

SINGLETON_INITIALIZER(AlchemyTable);

void AlchemyTable::Init()
{
    AlchemyData smallPotion = AlchemyData(0, 1);
    smallPotion.AddIngredient(10000, 10);
    smallPotion.AddIngredient(10001, 10);

    alchemyDataList.push_back(smallPotion);
}

AlchemyData* AlchemyTable::GetAlchemyData(int id)
{
    assert(id >= 0 && id < static_cast<int>(alchemyDataList.size()));
    assert(!alchemyDataList.empty());

    for (auto& data : alchemyDataList)
    {
        if (data.id == id)
        {
            return &data;
        }
    }

    return nullptr;
}

vector<AlchemyData>& AlchemyTable::GetAllAlchemyData()
{
    return alchemyDataList;
}
