#ifndef ALCHEMY_TABLE_H
#define ALCHEMY_TABLE_H

#include "SingletonMacro.h"
#include "AlchemyData.h"

#include <vector>
#include <memory>
#include <unordered_set>

using namespace std;

class AlchemyTable
{
    SINGLETON_WITH_INIT(AlchemyTable)
public:
    shared_ptr<AlchemyData> GetAlchemyData(int id);
    vector<shared_ptr<AlchemyData>>& GetAllAlchemyData();
private:
    void Init();

private:
    vector<shared_ptr<AlchemyData>> alchemyDataList;
};

#endif // !ALCHEMY_TABLE_H