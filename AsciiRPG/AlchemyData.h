#ifndef ALCHEMY_DATA_H
#define ALCHEMY_DATA_H

#include "Enums.h"

#include <vector>
#include <string>

using namespace std;

class AlchemyDataElement
{
public:
    int itemKey;
    int quantity;
};

class AlchemyData
{
public:
    vector<string> GetRenderString() const;

public:
    int key;
    /// <summary>
    /// at this moment, only consumable item is supported. So, the resultItemKey is the key of the consumable item in the ConsumableItemTable.
    /// but in the future, if we support other item types, we need to add a resultItemType field to specify the type of the result item.
    /// </summary>
    int resultItemKey;
    ItemType itemType;
    vector<AlchemyDataElement> ingredients;
};

#endif // !ALCHEMY_DATA_H
