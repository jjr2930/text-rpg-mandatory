#ifndef ITEM_TABLE_H
#define ITEM_TABLE_H

#include "Enums.h"
#include "SingletonMacro.h"
#include "IItem.h"

#include <string>
#include <unordered_map>

using namespace std;

/// <summary>
/// TODO: name changed to ConsumableItemData
/// </summary>
class ConsumableItemData : public IItem
{
public:
    ConsumableItemData();
public:
    int cost;
    StatType statType;
    OperatorType operatorType;
    float amount;
    bool isInstant;
    double duration;
    double interval;
};

/// <summary>
/// TODO: Tables has same feature so it should be refactored
/// </summary>
class ConsumableItemTable
{
public:
    SINGLETON_WITH_INIT(ConsumableItemTable)

public:
    const shared_ptr<ConsumableItemData> GetData(int id) const;
    const string GetItemName(int id) const;

    shared_ptr<IItem> GetRandomItem() const;
private:
    void Init();

private:
    unordered_map<int, shared_ptr<ConsumableItemData>> data;

};
#endif // !ITEM_TABLE_H