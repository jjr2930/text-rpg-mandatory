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

#include <cassert>

#include <iostream>

int main()
{

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

    Monster* monster = new Slime("슬라임",
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
    }
}