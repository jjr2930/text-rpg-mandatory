#ifndef ITEMDROP_TABLE_H
#define ITEMDROP_TABLE_H

#include <string>
#include <vector>
#include <memory>

#include "SingletonMacro.h"

using namespace std;

/// <summary>
/// TODO change name to MonsterDropItemData
/// </summary>
class MonsterItemDropData
{
public:
    int key;
    int minQuantity;
    int maxQuantity;
    double dropChance;
};

/// <summary>
/// TODO: Chagne name to monsterDropItemGroup
/// </summary>
class MonsterItemDropGroup
{
public:
    int key;
    string name;
    vector<shared_ptr<MonsterItemDropData>> dropItems;
};

/// <summary>
/// todo: change name to MonsterDropItemTable
/// </summary>
class MonsterItemDropTable
{
public:
    SINGLETON_WITH_INIT(MonsterItemDropTable);

public:
    const vector<shared_ptr<MonsterItemDropData>>& GetDropItems(int dropGroupKey) const;

private:
    void Init();

private:
    vector<MonsterItemDropGroup> dropGroups;
};

#endif // ! ITEMDROP_TABLE_H
