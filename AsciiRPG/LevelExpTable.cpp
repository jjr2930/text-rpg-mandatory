#include "LevelExpTable.h"

SINGLETON_INITIALIZER(LevelExpTable)

void LevelExpTable::Init()
{
    levelExpMap = {
        {2, 10},
        {3, 30},
        {4, 60},
        {5, 100},
        {6, 150},
        {7, 210},
        {8, 280},
        {9, 360},
        {10, 450}
    };

    //levelExpMap = {
    //    {2, 100},
    //    {3, 300},
    //    {4, 600},
    //    {5, 1000},
    //    {6, 1500},
    //    {7, 2100},
    //    {8, 2800},
    //    {9, 3600},
    //    {10, 4500}
    //};
}

int LevelExpTable::GetExpForLevel(int level) const
{
    auto it = levelExpMap.find(level);
    if (it != levelExpMap.end())
    {
        return it->second;
    }

    return -1;
}