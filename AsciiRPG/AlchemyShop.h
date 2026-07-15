#ifndef ALCHEMY_SHOP_H
#define ALCHEMY_SHOP_H

#include "Vector2Int.h"
#include "Enums.h"
#include "InteractableObject.h"

#include <vector>
#include <string>
#include <stack>

class EventParameter;

using namespace std;

class AlchemyShop : public InteractableObject
{
public:
    static constexpr int MAX_DISPLAY_RECIPES = 20;
    static constexpr char SHOP_TITLE[] = "=== Alchemy Shop ===";

    using InteractableObject::InteractableObject;
    AlchemyShop(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    virtual vector<string> GetRenderStrings() const;

    void IncreaseCursorIndex() override;
    void DecreaseCursorIndex() override;
    void ConfirmSelection() override;
    void OnCancel() override;
    void Reset() override;
    void OnDisable() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
    void ProcessMainMenuInput(char inputChar);
    void ProcessRecipeListInput(char inputChar);

private:
    vector<string> mainMenuOptions;
    Vector2Int recipeDisplayRange;
    stack<AlchemyShopState> stateStack;
    int mainMenuCursor;
    int recipeListCursor;
    int findRecipeCursor;
    string playerInput;
};

#endif // !ALCHEMY_SHOP_H
