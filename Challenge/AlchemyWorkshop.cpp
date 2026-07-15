#include "AlchemyWorkshop.h"
#include <iostream>

using namespace std;

Ingredient::Ingredient(const std::string& name, int quantity)
    : name(name)
    , quantity(quantity)
{}

std::string Ingredient::GetName() const
{
    return name;
}

int Ingredient::GetQuantity() const
{
    return quantity;
}

PotionRecipe::PotionRecipe(const std::string& name, const std::vector<Ingredient>& ingredients)
    : name(name)
    , ingredients(ingredients)
{
}

std::string PotionRecipe::GetName() const
{
    return name;
}

const std::vector<Ingredient>& PotionRecipe::GetIngredients() const
{
    return ingredients;
}

/*
=== 포션 제작소 ===
1. 전체 레시피 보기
2. 포션 이름으로 검색
3. 재료로 검색
0. 돌아가기

선택: 2
검색할 포션 이름: HP포션
-> HP포션: 허브 x1, 맑은물 x1

선택: 3
검색할 재료: 허브
-> HP포션 (허브 x1, 맑은물 x1)
-> 스태미나포션 (허브 x1, 베리 x1)
총 2개의 레시피를 찾았습니다.
*/

AlchemyWorkshop::AlchemyWorkshop()
{
    recipes.push_back(PotionRecipe("HP포션", { Ingredient("허브", 1), Ingredient("맑은물", 1) }));
    recipes.push_back(PotionRecipe("스태미나포션", { Ingredient("허브", 1), Ingredient("베리", 1) }));
}

AlchemyShopMenuSelectionType AlchemyWorkshop::PrintMenu()
{
    cout << "=== 포션 제작소 ===" << endl;
    cout << "1. 전체 레시피 보기" << endl;
    cout << "2. 포션 이름으로 검색" << endl;
    cout << "3. 재료로 검색" << endl;
    cout << "0. 돌아가기" << endl;
    cout << endl;
    cout << "선택: ";

    int choice;
    while (true)
    {
        cin >> choice;
        switch (choice)
        {
            case 0: return AlchemyShopMenuSelectionType::Exit;
            case 1: return AlchemyShopMenuSelectionType::ShowAllRecipes;
            case 2: return AlchemyShopMenuSelectionType::SearchByName;
            case 3: return AlchemyShopMenuSelectionType::SearchByIngredient;
            default:
                cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
                break;
        }
    }
}

void AlchemyWorkshop::ShowAllRecipes()
{
    for (auto& recipe : recipes)
    {
        cout << "-> " << recipe.GetName() << ": ";
        const auto& ingredients = recipe.GetIngredients();
        for (size_t i = 0; i < ingredients.size(); ++i)
        {
            cout << ingredients[i].GetName() << " x" << ingredients[i].GetQuantity();
            if (i < ingredients.size() - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

void AlchemyWorkshop::SearchByName(const std::string & name)
{
    bool found = false;
    for (auto& recipe : recipes)
    {
        if (recipe.GetName() == name)
        {
            cout << "-> " << recipe.GetName() << ": ";
            const auto& ingredients = recipe.GetIngredients();
            for (size_t i = 0; i < ingredients.size(); ++i)
            {
                cout << ingredients[i].GetName() << " x" << ingredients[i].GetQuantity();
                if (i < ingredients.size() - 1)
                    cout << ", ";
            }
            cout << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "찾을 수 없습니다." << endl;
    }
}

void AlchemyWorkshop::SearchByIngredient(const std::string& ingredient)
{
    int count = 0;
    for (auto& recipe : recipes)
    {
        const auto& ingredients = recipe.GetIngredients();
        for (const auto& ing : ingredients)
        {
            if (ing.GetName() == ingredient)
            {
                cout << "-> " << recipe.GetName() << " (";
                for (size_t i = 0; i < ingredients.size(); ++i)
                {
                    cout << ingredients[i].GetName() << " x" << ingredients[i].GetQuantity();
                    if (i < ingredients.size() - 1)
                        cout << ", ";
                }
                cout << ")" << endl;
                count++;
                break;
            }
        }
    }
    cout << "총 " << count << "개의 레시피를 찾았습니다." << endl;

}