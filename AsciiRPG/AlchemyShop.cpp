#include "AlchemyShop.h"
#include "AlchemyTable.h"
#include "ItemTable.h"
#include "Const.h"
#include "ObjectManager.h"
#include "EventParameter.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <format>

AlchemyShop::AlchemyShop(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : InteractableObject(id, name, params)
    , recipeDisplayRange{ 0, MAX_DISPLAY_RECIPES - 1 }
    , mainMenuCursor(-1)
    , recipeListCursor(-1)
{
    stateStack.push(AlchemyShopState::MainMenu);
    mainMenuOptions = { "View Recipes", "Find Recipes", "Craft", "Exit" };
}

vector<string> AlchemyShop::GetRenderStrings() const
{
    vector<string> result;
    result.emplace_back(SHOP_TITLE);
    switch (stateStack.top())
    {
        case AlchemyShopState::MainMenu:
            {
                for (size_t i = 0; i < mainMenuOptions.size(); ++i)
                {
                    if (mainMenuCursor == i)
                    {
                        result.emplace_back(format("> {} <", mainMenuOptions[i]));
                    }
                    else
                    {
                        result.emplace_back(format("  {}  ", mainMenuOptions[i]));
                    }
                }
            }
            break;

        case AlchemyShopState::RecipeList:
            {
                auto& alchemyDataList = AlchemyTable::GetInstance().GetAllAlchemyData();
                for (int i = recipeDisplayRange.x; i <= recipeDisplayRange.y && i < alchemyDataList.size(); i++)
                {
                    string itemName = ItemTable::GetInstance().GetItemName(alchemyDataList[i].resultItemKey);
                    string displayText = itemName + ": ";
                    for (const auto& ingredient : alchemyDataList[i].ingredients)
                    {
                        string ingredientName = ItemTable::GetInstance().GetItemName(ingredient.itemKey);
                        displayText += ingredientName + " x" + to_string(ingredient.quantity) + " ";
                    }
                    result.emplace_back(displayText);
                }

                result.emplace_back("Up : cursor up");
                result.emplace_back("Down : cursor down");

            }
            break;

        case AlchemyShopState::FindRecipe:
            {
                result.emplace_back("Ingredient : " + playerInput);

                result.emplace_back("Up: Cursor up");
                result.emplace_back("Down: Cursor down");
            }
            break;
    }

    return result;
}

void AlchemyShop::IncreaseCursorIndex()
{
    int mainmenuOptionsCount = static_cast<int>(mainMenuOptions.size());

    switch (stateStack.top())
    {
        case AlchemyShopState::MainMenu:
            mainMenuCursor = (mainMenuCursor + 1) % mainmenuOptionsCount;
            break;

        case AlchemyShopState::RecipeList:
            {
                auto& alchemyDataList = AlchemyTable::GetInstance().GetAllAlchemyData();
                int recipeListCount = static_cast<int>(alchemyDataList.size());
                if (recipeListCursor < recipeListCount - 1)
                {
                    recipeListCursor++;
                    if (recipeListCursor > recipeDisplayRange.y)
                    {
                        recipeDisplayRange.x++;
                        recipeDisplayRange.y++;
                    }
                }
            }
            break;
    }
}

void AlchemyShop::DecreaseCursorIndex()
{
    switch (stateStack.top())
    {
        case AlchemyShopState::MainMenu:
            mainMenuCursor = (mainMenuCursor - 1 + mainMenuOptions.size()) % mainMenuOptions.size();            
            break;

        case AlchemyShopState::RecipeList:
            {
                auto& alchemyDataList = AlchemyTable::GetInstance().GetAllAlchemyData();
                if (recipeListCursor > 0)
                {
                    recipeListCursor--;
                    if (recipeListCursor < recipeDisplayRange.x)
                    {
                        recipeDisplayRange.x--;
                        recipeDisplayRange.y--;
                    }
                }
            }
            break;
    }
}

void AlchemyShop::ConfirmSelection()
{
    switch (stateStack.top())
    {
        case AlchemyShopState::MainMenu:
            switch (mainMenuCursor)
            {
                case 0: // View Recipes
                    stateStack.push(AlchemyShopState::RecipeList);
                    Reset();
                    recipeDisplayRange = { 0, MAX_DISPLAY_RECIPES - 1 };
                    break;
                case 1: // Find Recipes by Ingredients
                    stateStack.push(AlchemyShopState::FindRecipe);
                    Reset();
                    break;
                case 2: // Craft
                    // Implement logic for crafting
                    break;
                case 3: // Exit
                    ObjectManager::GetInstance().BroadcastEvent(make_shared<InteractionCanceledEventParameter>());
                    break;
            }
            break;
        default:
            break;
    }
}

void AlchemyShop::OnCancel()
{
    switch (stateStack.top())
    {
        case AlchemyShopState::MainMenu:
            Reset();
            ObjectManager::GetInstance().BroadcastEvent(make_shared<InteractionCanceledEventParameter>());
            break;

        case AlchemyShopState::RecipeList:
            Reset();
            stateStack.pop();
            break;


        default:
            break;
    }
}

void AlchemyShop::Reset()
{
    mainMenuCursor = 0;
    recipeListCursor = 0;
    playerInput.clear();
}

void AlchemyShop::OnDisable()
{
    mainMenuCursor = -1;
    recipeListCursor = -1;
}

void AlchemyShop::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::KeyPressed:
            {
                auto inputMessage = static_cast<InputEventParameter*>(message.get());
                switch (stateStack.top())
                {
                    case AlchemyShopState::MainMenu:
                        ProcessMainMenuInput(inputMessage->key);
                        break;

                    case AlchemyShopState::RecipeList:
                        ProcessRecipeListInput(inputMessage->key);
                        break;


                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void AlchemyShop::ProcessMainMenuInput(Virtualkey inputKey)
{
    switch (inputKey)
    {
        case Virtualkey::Up: 
            DecreaseCursorIndex();
            break;

        case Virtualkey::Down:  
            IncreaseCursorIndex();
            break;

        case Virtualkey::Space: // Enter key
            ConfirmSelection();
            break;

        case Virtualkey::Escape: // Escape key
            OnCancel();
            break;

        default:
            break;
    }
}

void AlchemyShop::ProcessRecipeListInput(Virtualkey inputKey)
{
    switch (inputKey)
    {
        case Virtualkey::Up:
            DecreaseCursorIndex();
            break;

        case Virtualkey::Left:
            IncreaseCursorIndex();
            break;

        case Virtualkey::Escape:
            OnCancel();
            break;

        default:
            break;
    }
}
