#ifndef ALCHEMY_DATA_H
#define ALCHEMY_DATA_H

#include <vector>

using namespace std;

struct AlchemyDataElement
{
    int itemKey;
    int quantity;
};

struct AlchemyData
{
public:
    AlchemyData(int id, int resultItemKey)
        : id(id), resultItemKey(resultItemKey)
    {}

    void AddIngredient(int itemKey, int quantity)
    {
        ingredients.push_back({ itemKey, quantity });
    }
public:
    int id;
    int resultItemKey;
    vector<AlchemyDataElement> ingredients;

};

#endif // !ALCHEMY_DATA_H
