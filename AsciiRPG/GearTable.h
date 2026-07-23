#ifndef GEAR_TABLE_H
#define GEAR_TABLE_H

#include <unordered_map>
#include <memory>

#include "IItem.h"
#include "Enums.h"
#include "SingletonMacro.h"

using namespace std;

class GearStatModifier
{
public:
    StatType statType;
    OperatorType operatorType;
    float amount;
};

class GearData : public IItem
{
    /*
    ItemType itemType;
    int key;
    string name;
    bool isUsable;
    int price;
    */

public:
    GearSlotType slot;
    int minLevel;
    vector<shared_ptr<GearStatModifier>> statModifiers;
};

class GearTable
{
public:
    SINGLETON_WITH_INIT(GearTable)
public:
    shared_ptr<GearData> GetData(int key) const;
    shared_ptr<IItem> GetRandomItem() const;
private:
    void Init();
private:
    unordered_map<int, shared_ptr<GearData>> gearDataMap;
};

#endif // !GEAR_TABLE_H
