#ifndef MENU_H
#define MENU_H
#include "Enums.h"

#include <string>

class Player;

class Menu
{
public:
    Menu();
    void PrintCreation();
    void PrintStatus(std::string name, int stat[]);
    void PrintStatusUsingSelf();
    JobType PrintJobSelection();
    MenuSelectionType PrintMainMenu();

    /*
    * getter
    */
    std::string&   GetName() const;
    int*            GetStat() const;

private:
    std::string name;
    int* stat;
};
#endif

