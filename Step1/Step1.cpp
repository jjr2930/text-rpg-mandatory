#include "Step1.h"

/*
===========================================
[ 던전 탈출 텍스트 RPG ]
===========================================
용사의 이름을 입력해주세요: 철수

HP와 MP를 입력해주세요: 80 60
공격력과 방어력을 입력해주세요: 40 25

====================================
철수 의 현재 능력치
====================================
HP: 80    MP: 60
공격력: 40    방어력: 25
====================================
*/

#include <iostream>

using namespace std;

Step1::Menu::Menu()
    : name(L"")
    , stat(new int[static_cast<int>(Step1::StatType::Size)] { 0, 0, 0, 0 })
{
}

void Step1::Menu::Run()
{         
    cout << "===========================================" << endl;
    cout << "[ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "===========================================" << endl;

    cout << "용사의 이름을 입력해주세요: ";
    getline(wcin, name) ;
    cout << endl;

    cout << "HP와 MP를 입력해주세요: ";
    cin >> stat[(int)(StatType::HP)] >> stat[(int)(StatType::MP)];
    cout << endl;

    cout << "공격력과 방어력을 입력해주세요: ";
    cin >> stat[static_cast<int>(StatType::Attack)] >> stat[static_cast<int>(StatType::Defense)];
    cout << endl;
    
    PrintStatus(name, stat);

    cin.ignore();
    cin.get();
}

void Step1::Menu::PrintStatus(std::wstring name, int stat[])
{
    cout << "===================================" << endl; 
    wcout << name << " 의 현재 능력치" << endl;
    cout << "===================================" << endl;
    cout << "HP: " << stat[(int)(Step1::StatType::HP)] 
        << "    MP: " << stat[(int)(Step1::StatType::MP)] << endl;
    cout << "공격력: " << stat[(int)(Step1::StatType::Attack)] 
        << "    방어력: " << stat[(int)(Step1::StatType::Defense)] << endl;
    cout << "===================================" << endl;

    cout << "계속하려면 아무 키나 누르세요..." << endl;                                                                                      
}
