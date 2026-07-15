#ifndef ALCHEMY_DATA_H
#define ALCHEMY_DATA_H

#include <vector>
#include <string>

using namespace std;

struct AlchemyDataElement
{
    int itemKey;
    int quantity;
};

struct AlchemyData
{
public:
    AlchemyData(int id, int resultItemKey);
    void AddIngredient(int itemKey, int quantity);
    vector<string> GetRenderString() const;

public:
    int id;
    int resultItemKey;
    vector<AlchemyDataElement> ingredients;
};

#endif // !ALCHEMY_DATA_H
