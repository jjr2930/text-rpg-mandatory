#ifndef ALCHEMY_WORKSHOP_H
#define ALCHEMY_WORKSHOP_H


/*
* === 포션 제작소 ===
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


**구현 항목**

- [ ]  결과 화면을 참고하여 `PotionRecipe` / `AlchemyWorkshop` 코드 구조 만들기
- [ ]  `vector<PotionRecipe>`에 레시피 저장하기
- [ ]  `ShowAllRecipes()`: 전체 레시피 출력하기
- [ ]  `SearchByName(string name)`: 이름이 일치하는 레시피 출력하기
- [ ]  이름 검색 결과가 없으면 "찾을 수 없습니다" 출력하기
- [ ]  `SearchByIngredient(string ingredient)`: 해당 재료를 포함한 레시피 전부 출력하기 (재료 개수는 2개로 제한되어 있음)
- [ ]  메인 메뉴에 "3. 포션 제작소" 추가하기

**주의할 점**

- 이 STEP의 목표는 "레시피 검색"입니다. 실제 포션 제작/사용은 도전 STEP에서 확장해도 됩니다.
- 문자열 비교가 정확히 일치해야 하는지, 일부만 포함해도 되는지 기준을 정하고 구현하세요.


*/

#include <string>
#include <vector>

#include "Enums.h"

class Ingredient
{
public:
    Ingredient(const std::string& name, int quantity);
    std::string GetName() const;
    int GetQuantity() const;

private:
    std::string name;
    int quantity;
};
class PotionRecipe
{
public:
    PotionRecipe(const std::string& name, const std::vector<Ingredient>& ingredients);
    std::string GetName() const;
    const std::vector<Ingredient>& GetIngredients() const;

private:
    std::string name;
    std::vector<Ingredient> ingredients;
};

class AlchemyWorkshop
{
public:
    AlchemyWorkshop();
    AlchemyShopMenuSelectionType PrintMenu();
    void ShowAllRecipes(); 
    void SearchByName(const std::string& name);
    void SearchByIngredient(const std::string& ingredient);

private:
    std::vector<PotionRecipe> recipes;

};

#endif // !ALCHEMY_WORKSHOP_H