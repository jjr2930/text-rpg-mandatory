#include "Menu.h"
#include "Enums.h"
#include "Player.h"
#include "Archer.h"
#include "Magician.h"
#include "Thief.h"
#include "Warrior.h"
#include "Monster.h"
#include "Slime.h"
#include "Const.h"
#include "AlchemyWorkshop.h"

#include <cassert>
#include <iostream>

int main()
{
    AlchemyWorkshop alchemyWorkshop;
    Menu menu;
    menu.PrintCreation();
    menu.PrintStatusUsingSelf();

    Player* player = nullptr;

    JobType selectedJob = menu.PrintJobSelection();
    switch (selectedJob)
    {
        case JobType::Warrior:
            player = new Warrior(menu.GetName(), menu.GetStat());
            break;

        case JobType::Magician:             
            player = new Magician(menu.GetName(), menu.GetStat());
            break;

        case JobType::Thief: 
            player = new Thief(menu.GetName(), menu.GetStat()); 
            break;

        case JobType::Archer: 
            player = new Archer(menu.GetName(), menu.GetStat()); 
            break;

        default:
            break;
    }

    player->PrintPlayerStatus();

    Monster* monster = nullptr;

    bool exitRequest = false;
    while (!exitRequest)
    {
        MainMenuSelectionType selection = menu.PrintMainMenu();
        switch (selection)
        {
            case MainMenuSelectionType::ExitGame:
                std::cout << "게임을 종료합니다." << std::endl;
                exitRequest = true;
                break;
            case MainMenuSelectionType::EnterDungeon:
                std::cout << "던전에 입장합니다." << std::endl;
                {
                    monster = new Slime("슬라임",
                        Const::SLIME::START_HP, 
                        Const::SLIME::START_ATTACK, 
                        Const::SLIME::START_DEFENSE);


                    while (player->GetHp() > 0 && monster->GetHp() > 0)
                    {
                        player->Attack(monster);
                        monster->Attack(player);
                    }

                    if (player->GetHp() <= 0 && monster->GetHp() <= 0)
                    {
                        std::cout << "플레이어와 몬스터가 동시에 패배했습니다." << std::endl;
                    }
                    else if (player->GetHp() <= 0)
                    {
                        std::cout << "플레이어가 패배했습니다." << std::endl;
                    }
                    else if (monster->GetHp() <= 0)
                    {
                        std::cout << "몬스터가 패배했습니다." << std::endl;
                        std::vector<MonsterDropItem> dropItems = monster->GetDropItems();
                        for ( auto& item : dropItems)
                        {
                            Item newItem(item);
                            player->AddItem(newItem);
                        }

                        player->PrintInventory();
                    }

                    delete monster;
                }
                break;
            case MainMenuSelectionType::PrintInventory:
                player->PrintInventory();
                break;

            case MainMenuSelectionType::PotionShop:
                {
                    auto alchemyMenuSelection = alchemyWorkshop.PrintMenu();
                    switch (alchemyMenuSelection)
                    {
                        case AlchemyShopMenuSelectionType::Exit:
                            break;

                        case AlchemyShopMenuSelectionType::ShowAllRecipes:
                            alchemyWorkshop.ShowAllRecipes();
                            break;

                        case AlchemyShopMenuSelectionType::SearchByName:
                            {
                                std::string name;
                                std::cout << "검색할 포션 이름: ";
                                std::cin >> name;
                                alchemyWorkshop.SearchByName(name);
                                break;
                            }
                        case AlchemyShopMenuSelectionType::SearchByIngredient:
                            {
                                std::string ingredient;
                                std::cout << "검색할 재료: ";
                                std::cin >> ingredient;
                                alchemyWorkshop.SearchByIngredient(ingredient);
                                break;
                            }
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }
    }

    delete player;  
    return 0;
}