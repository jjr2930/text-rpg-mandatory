#ifndef ALCHEMY_TABLE_H
#define ALCHEMY_TABLE_H

#include "SingletonMacro.h"
#include "AlchemyData.h"

#include <vector>
#include <memory>

using namespace std;

class AlchemyTable
{
    SINGLETON_WITH_INIT(AlchemyTable)
public:
    void Init();
    shared_ptr<AlchemyData> GetAlchemyData(int id);
    vector<shared_ptr<AlchemyData>>& GetAllAlchemyData();


private:
    vector<shared_ptr<AlchemyData>> alchemyDataList;
};

#endif // !ALCHEMY_TABLE_H