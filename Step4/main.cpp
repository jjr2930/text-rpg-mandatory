#include "Menu.h"
#include "Enums.h"
#include "Player.h"
#include "Archer.h"
#include "Magician.h"
#include "Thief.h"
#include "Warrior.h"
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
    player->Attack();
}