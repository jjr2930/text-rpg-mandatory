#include "AlchemyShop.h"
#include "AlchemyTable.h"
#include "ItemTable.h"

#include <iostream>
#include <string>
#include <conio.h>

AlchemyShop::AlchemyShop()
    : recipeDisplayRange{0, MAX_DISPLAY_RECIPES - 1}
{}

void AlchemyShop::Render()
{
    switch (shopState)
    {
        case AlchemyShopState::MainMenu:
            RenderMainMenu();
            break;

        case AlchemyShopState::RecipeList:
            RenderRecipeList();
            break;

        default:
            break;
    }
}

void AlchemyShop::RenderMainMenu()
{
    int menuSelectionNumber = 0;
    while(true)
    {
        cout << "=== Alchemy Shop ===" << std::endl;
        cout << "1. View Recipes" << std::endl;
        cout << "2. Find Recipes by Ingredients" << std::endl;
        cout << "3. Craft" << std::endl;
        cout << "4. Exit" << std::endl;
        
        cin >> menuSelectionNumber;
        if (1 <= menuSelectionNumber && menuSelectionNumber <= 4)
        {
            break;
        }
        else
        {
            cout << "Invalid selection. Please try again." << std::endl;
        }
    }

    shopState = static_cast<AlchemyShopState>(menuSelectionNumber - 1);
}

void AlchemyShop::RenderRecipeList()
{
    auto& alchemyDataList = AlchemyTable::GetInstance().GetAllAlchemyData();
    for (int i = recipeDisplayRange.x; i <= recipeDisplayRange.y && i < alchemyDataList.size(); i++)
    {
        string itemName = ItemTable::GetInstance().GetItemName(alchemyDataList[i].resultItemKey);
        cout << itemName << ": ";
        for (const auto& ingredient : alchemyDataList[i].ingredients)
        {
            string ingredientName = ItemTable::GetInstance().GetItemName(ingredient.itemKey);
            cout << ingredientName << " x" << ingredient.quantity << " ";
        }
        cout << std::endl;
    }

    char input;
    while (true)
    {
        input = _getch();
        switch (input)
        { 
            case 'w': case 'W':
                if (recipeDisplayRange.x > 0)
                {
                    recipeDisplayRange.x--;
                    recipeDisplayRange.y--;
                }
                break;

            case 's': case 'S':
                if (recipeDisplayRange.y < AlchemyTable::GetInstance().GetAllAlchemyData().size() - 1)
                {
                    recipeDisplayRange.x++;
                    recipeDisplayRange.y++;
                }
                break;
            default:
                break;
        }
    }
}
