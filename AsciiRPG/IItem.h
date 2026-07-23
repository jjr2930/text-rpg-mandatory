#ifndef IITEM_H
#define IITEM_H

#include "Enums.h"

#include <string>

using namespace std;

class IItem
{
public:
    virtual ~IItem() = default;

    ItemType itemType;
    int key;
    string name;
    bool isUsable;
    int cost;
};

#endif // ! IITEM_H