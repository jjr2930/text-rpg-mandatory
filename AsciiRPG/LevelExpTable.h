#ifndef LEVEL_EXP_TABLE_H
#define LEVEL_EXP_TABLE_H

#include "SingletonMacro.h"

#include <unordered_map>

using namespace std;

class LevelExpTable
{
    SINGLETON_WITH_INIT(LevelExpTable)
        
public:
    int GetExpForLevel(int level) const;
private:
    void Init();

private:
    unordered_map<int, int> levelExpMap;
};

#endif // !LEVEL_EXP_TABLE_H