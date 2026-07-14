#ifndef ITEM_DATA_H
#define ITEM_DATA_H

#include "Enums.h"

#include <string>

using namespace std;

struct ItemData
{
    int id;
    string name;
    int cost;
    bool isUsable;
    StatType statType;
    OperatorType operatorType;
    float amount;
    bool isInstant;
    double duration;
    double interval;
};

#endif // !ITEM_DATA_H
