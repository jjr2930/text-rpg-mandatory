#ifndef DROPITEMDATA_H
#define DROPITEMDATA_H  

#include <string>

using namespace std;

class DropItemData
{
public:
    DropItemData(const string& itemName, int count)
        : itemName(itemName), count(count) {}

public:
    string GetItemName() const { return itemName; }
    int GetCount() const { return count; }

private:
    string itemName;
    int count;
};

#endif