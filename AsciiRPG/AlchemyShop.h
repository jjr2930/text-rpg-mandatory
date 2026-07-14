#ifndef ALCHEMY_SHOP_H
#define ALCHEMY_SHOP_H

#include "Vector2Int.h"
#include "Enums.h"

#include <vector>
#include <string>

using namespace std;

class AlchemyShop
{
public:
    static constexpr int MAX_DISPLAY_RECIPES = 10;

    AlchemyShop();

    void Render();
    void SetMainMenuCursor(int cursor);
    void SetRecipeDisplayRange(const Vector2Int& range);

private:
    void RenderMainMenu();
    void RenderRecipeList();

private:
    AlchemyShopState shopState;
    int mainMenuCursor;
    Vector2Int recipeDisplayRange;
};

#endif // !ALCHEMY_SHOP_H
