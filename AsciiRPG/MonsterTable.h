#ifndef MONSTER_TABLE_H
#define MONSTER_TABLE_H

#include <vector>
#include <memory>
#include <string>

#include "SingletonMacro.h"

using namespace std;

class MonsterData
{
public:
    int key;
    string name;
    char displayChar;
    int dropTableKey;
    int minFloor;
    int maxFloor;
    float hp;
    float attack;
    float defense;
    int exp;
    double attackDelay;
};

class MonsterTable
{
public:
    SINGLETON_WITH_INIT(MonsterTable)

public:
    shared_ptr<MonsterData> GetMonsterData(int key) const;
    shared_ptr<MonsterData> GetMonsterData(char displayChar) const;
    vector<shared_ptr<MonsterData>> GetMonstersByFloor(int floor) const;
    bool IsExist(char displayChar) const;
private:
    void Init();

private:
    vector<shared_ptr<MonsterData>> monsterDataList;
};

#endif // !MONSTER_TABLE_H
