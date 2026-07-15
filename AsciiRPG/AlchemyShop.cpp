#include "AlchemyShop.h"
#include "AlchemyTable.h"
#include "ItemTable.h"
#include "Const.h"
#include "ObjectManager.h"
#include "EventParameter.h"
#include "ItemData.h"
#include "Player.h"
#include "Logger.h"

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
    , findRecipeCursor(-1)
    , craftCusor(-1)
{
    stateStack.push(AlchemyShopState::MainMenu);
    mainMenuOptions = { "View Recipes", "Find Recipes", "Craft", "Exit" };
}

vector<string> AlchemyShop::GetRenderStrings()
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
                    auto renderStrings = alchemyDataList[i]->GetRenderString();
                    for (const auto& line : renderStrings)
                    {
                        result.emplace_back(line);
                    }
                }

                result.emplace_back("Up : cursor up");
                result.emplace_back("Down : cursor down");
                result.emplace_back("ESC : back");
            }
            break;

        case AlchemyShopState::FindRecipe:
            {
                result.emplace_back("Ingredient : " + playerInput);
                auto recipes = FindRecipesByIngredient(playerInput);
                for (auto& recipe : recipes)
                {
                    auto renderStrings = recipe->GetRenderString();
                    for (const auto& line : renderStrings)
                    {
                        result.emplace_back(line);
                    }
                }

                result.emplace_back("Up: Cursor up");
                result.emplace_back("Down: Cursor down");
            }
            break;

        case AlchemyShopState::Craft:
            {
                for (size_t i = 0; i < candidateRecipes.size(); ++i)
                {
                    string itemName = ItemTable::GetInstance().GetItemName(candidateRecipes[i]->resultItemKey);
                    if (craftCusor == i)
                    {
                        result.emplace_back(format("> {} <", itemName));
                    }
                    else
                    {
                        result.emplace_back(format("  {}  ", itemName));
                    }
                }
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

        case AlchemyShopState::Craft:
            {
                auto& alchemyDataList = AlchemyTable::GetInstance().GetAllAlchemyData();
                int craftCount = static_cast<int>(alchemyDataList.size());
                if (craftCusor < craftCount - 1)
                {
                    craftCusor++;
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

        case AlchemyShopState::Craft:
            {
                if (craftCusor > 0)
                {
                    craftCusor--;
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
                //TODO : Make enum class
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
                    stateStack.push(AlchemyShopState::Craft);
                    BuildCandidateRecipesList();
                    Reset();
                    break;
                case 3: // Exit
                    ObjectManager::GetInstance().BroadcastEvent(make_shared<InteractionCanceledEventParameter>());
                    break;
            }
            break;

        case AlchemyShopState::Craft:
            {
                auto recipe = candidateRecipes[craftCusor];
                
                //checking possible to craft
                shared_ptr<Player> player = ObjectManager::GetInstance().GetObjectByType<Player>();
                
                for (const auto& ingredient : recipe->ingredients)
                {
                    if (!player->HasEnoughItem(ingredient.itemKey, ingredient.quantity))
                    {
                        Logger::LogInfo("Not enough ingredients to craft " + ItemTable::GetInstance().GetItemName(recipe->resultItemKey));
                        return;
                    }
                }

                player->AddItemQuantity(recipe->resultItemKey, 1);

                //succeed
                for (const auto& ingredient : recipe->ingredients)
                {
                    player->AddItemQuantity(ingredient.itemKey, -ingredient.quantity);
                }

                BuildCandidateRecipesList();
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

        case AlchemyShopState::FindRecipe:
            Reset();
            stateStack.pop();
            break;

        case AlchemyShopState::Craft:
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
    findRecipeCursor = 0;
    craftCusor = 0;
    playerInput.clear();
}

void AlchemyShop::OnDisable()
{
    mainMenuCursor = -1;
    recipeListCursor = -1;
    findRecipeCursor = -1;
    craftCusor = -1;
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

                    case AlchemyShopState::FindRecipe:
                        ProcessFindRecipeInput(inputMessage->key);
                        break;

                    case AlchemyShopState::Craft:
                        ProcessCraftInput(inputMessage->key);
                        break;
                    default:
                        break;
                }
            }
            break;

        case EventType::OnMapClearRequested:
            {
                DestroyEntity();
            }
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

        case Virtualkey::Down:
            IncreaseCursorIndex();
            break;

        case Virtualkey::Escape:
            OnCancel();
            break;
    }
}

void AlchemyShop::ProcessFindRecipeInput(Virtualkey inputKey)
{
    switch (inputKey)
    {
        case Virtualkey::Up:
            DecreaseCursorIndex();
            break;

        case Virtualkey::Down:
            IncreaseCursorIndex();
            break;

        case Virtualkey::Escape:
            OnCancel();
            break;

        case Virtualkey::Left:
        case Virtualkey::Right:
            //nothing to do
            break;

        case Virtualkey::Backspace:
            if (playerInput.size() > 0)
                playerInput.pop_back();
            break;

        default:
            playerInput += static_cast<char>(EnumUtility::ToKeyCode(inputKey));
            break;
    }
}

void AlchemyShop::ProcessCraftInput(Virtualkey inputKey)
{
    switch (inputKey)
    {
        case Virtualkey::Space:
            ConfirmSelection();
            break;

        case Virtualkey::Up:
            DecreaseCursorIndex();
            break;

        case Virtualkey::Down:
            IncreaseCursorIndex();
            break;

        case Virtualkey::Escape:
            OnCancel();
            break;

        default:
            break;
    }
}

vector<shared_ptr<AlchemyData>> AlchemyShop::FindRecipesByIngredient(const string& name)
{
    auto& alchemyData = AlchemyTable::GetInstance().GetAllAlchemyData();
    vector<shared_ptr<AlchemyData>> result;
    result.reserve(alchemyData.size());

    if (name.empty())
        return alchemyData;

    for (auto& data : alchemyData)
    {
        for (auto& ingredient : data->ingredients)
        {
            string ingredientName = ItemTable::GetInstance().GetItemName(ingredient.itemKey);
            if (ingredientName.find(name) != string::npos)
            {
                result.emplace_back(data);
                break;
            }
        }
    }

    // Implement filtering logic here
    return result;
}

void AlchemyShop::BuildCandidateRecipesList()
{
    shared_ptr<Player> player = ObjectManager::GetInstance().GetObjectByType<Player>();
    vector<InventoryItem> inventoryItems = player->GetInventory();
    auto& allAlchemyData = AlchemyTable::GetInstance().GetAllAlchemyData();
    
    candidateRecipes.clear();
    for (auto& iter : allAlchemyData)
    {
        bool canCraft = true;
        for (auto& ingredient : iter->ingredients)
        {
            bool hasIngredient = false;
            for (auto& item : inventoryItems)
            {
                if (item.GetTableKey() == ingredient.itemKey)
                {
                    hasIngredient = true;
                    break;
                }
            }
            if (!hasIngredient)
            {
                canCraft = false;
                break;
            }
        }
        if (canCraft)
        {
            candidateRecipes.emplace_back(iter);
        }
    }
}
