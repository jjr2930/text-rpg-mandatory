#include "Menu.h"
#include "Const.h"
#include "Enums.h"

#include <iostream>

using namespace std;

Menu::Menu() 
    : stat(new int[4] {0, 0, 0, 0})
{ 
}

void Menu::PrintCreation()
{
    cout << "===========================================" << endl;
    cout << "[ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "===========================================" << endl;

    cout << "용사의 이름을 입력해주세요: ";
    getline(cin, name) ;
    cout << endl;
    while (true)
    {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> stat[(int)(StatType::HP)] >> stat[(int)(StatType::MP)];
        cout << endl;

        if(stat[(int)(StatType::HP)] > Const::PLAYER::MIN_STAT && stat[(int)(StatType::MP)] > Const::PLAYER::MIN_STAT)
        {
            break;
        }
        else
        {
            cout << "HP와 MP는 최소 " << Const::PLAYER::MIN_STAT << " 초과해야 합니다." << endl;
        }
    }
    cout << "공격력과 방어력을 입력해주세요: ";

    while (true)
    {
        cin >> stat[(int)(StatType::Attack)] >> stat[(int)(StatType::Defense)];
        cout << endl;
        if (stat[(int)(StatType::Attack)] > Const::PLAYER::MIN_STAT && stat[(int)(StatType::Defense)] > Const::PLAYER::MIN_STAT)
        {
            break;
        }
        else
        {
            cout << "공격력과 방어력은 최소 " << Const::PLAYER::MIN_STAT << " 초과해야 합니다." << endl;
        }
    }
}

void Menu::PrintStatus(std::string name, int stat[])
{
    cout << "===================================" << endl; 
    cout << name << " 의 현재 능력치" << endl;
    cout << "===================================" << endl;
    cout << "HP: " << stat[(int)(StatType::HP)] 
        << "    MP: " << stat[(int)(StatType::MP)] << endl;
    cout << "공격력: " << stat[(int)(StatType::Attack)] 
        << "    방어력: " << stat[(int)(StatType::Defense)] << endl;
    cout << "===================================" << endl;     
}   


void Menu::PrintStatusUsingSelf()
{
    PrintStatus(name, stat);
}

/*
철수님, 직업을 선택해주세요!
1. 전사   2. 마법사   3. 도적   4. 궁수
선택: 2
*/
JobType Menu::PrintJobSelection()
{
    bool loop = true;
    while (loop)
    {
        cout << name << "님, 직업을 선택해주세요!" << endl;
        cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;

        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1: return JobType::Warrior;
            case 2: return JobType::Magician;
            case 3: return JobType::Thief;
            case 4: return JobType::Archer;

            default:
                cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
                break;
        }
    }

    return JobType::None;
}


/*
* 
=== 메인 메뉴 ===
1. 던전 입장
2. 인벤토리 확인
0. 게임 종료
*/
MenuSelectionType Menu::PrintMainMenu()
{
    cout << "=== 메인 메뉴 ===" << endl;
    cout << "1. 던전 입장" << endl;
    cout << "2. 인벤토리 확인" << endl;
    cout << "0. 게임 종료" << endl;

    int choice;
    while (true)
    {
        cin >> choice;
        switch (choice)
        {
            case 0: return MenuSelectionType::ExitGame;
            case 1: return MenuSelectionType::EnterDungeon;
            case 2: return MenuSelectionType::PrintInventory;
            default:
                cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
                break;
        }
    }
}


std::string& Menu::GetName() const
{
    return const_cast<std::string&>(name);
}
    
int* Menu::GetStat() const
{
    return stat;
}
