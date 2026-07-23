#ifndef ALCHEMY_SHOP_H
#define ALCHEMY_SHOP_H

#include "Vector2Int.h"
#include "Enums.h"
#include "InteractableObject.h"

#include <vector>
#include <string>
#include <stack>

class EventParameter;
class ConsumableItemData;
class AlchemyData;

using namespace std;

class AlchemyShop : public InteractableObject
{
public:
    static constexpr int DISPLAY_RECIPES_COUNTS_IN_PAGE = 5;
    static constexpr char SHOP_TITLE[] = "=== Alchemy Shop ===";

    using InteractableObject::InteractableObject;
    AlchemyShop(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    virtual vector<string> GetRenderStrings();

    void IncreaseCursorIndex() override;
    void DecreaseCursorIndex() override;
    void ConfirmSelection() override;
    void OnCancel() override;
    void Reset() override;
    void OnDisable() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
    void ProcessMainMenuInput(Virtualkey inputKey);
    void ProcessRecipeListInput(Virtualkey inputKey);
    void ProcessFindRecipeInput(Virtualkey inputKey);
    void ProcessCraftInput(Virtualkey inputKey);
    vector<shared_ptr<AlchemyData>> FindRecipesByIngredient(const string& name);
    void BuildCandidateRecipesList();
private:
    vector<string> mainMenuOptions;
    stack<AlchemyShopState> stateStack;
    vector<shared_ptr<AlchemyData>> candidateRecipes;
    int mainMenuCursor;
    int recipeListPageIndex;
    int findRecipeCursor;
    int craftCursor;
    string playerInput;
};

#endif // !ALCHEMY_SHOP_H
