#ifndef DROPITEMDATA_H
#define DROPITEMDATA_H  

#include <string>

using namespace std;

class DropItemData
{
public:
    DropItemData(int tableKey, int count)
        : tableKey(tableKey), count(count) {}

public:
    int GetTableKey() const { return tableKey; }
    int GetCount() const { return count; }

private:
    int tableKey;
    int count;
};

#endif