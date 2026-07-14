#ifndef ALCHEMY_TABLE_H
#define ALCHEMY_TABLE_H

#include "SingletonMacro.h"
#include "AlchemyData.h"

#include <vector>

using namespace std;

class AlchemyTable
{
    SINGLETON_WITH_INIT(AlchemyTable)
public:
    void Init();
    AlchemyData* GetAlchemyData(int id);
    vector<AlchemyData>& GetAllAlchemyData();


private:
    vector<AlchemyData> alchemyDataList;
};

#endif // !ALCHEMY_TABLE_H