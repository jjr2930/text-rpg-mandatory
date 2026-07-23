#ifndef INGREDIENT_TABLE_H
#define INGREDIENT_TABLE_H

#include "IItem.h"
#include "SingletonMacro.h"

#include <string>
#include <vector>
#include <memory>

using namespace std;

class IngredientData : public IItem
{
public:
    IngredientData();
};

class IngredientTable
{
public:
    SINGLETON_WITH_INIT(IngredientTable)

public:
    shared_ptr<IngredientData> GetData(int key) const;
    shared_ptr<IItem> GetRandomItem() const;

private:
    void Init();

private:

    /// <summary>
    /// TODO: it should change to unordered_map
    /// </summary>
    vector<shared_ptr<IngredientData>> ingredientDataList;
};

#endif // !INGREDIENT_TABLE_H

