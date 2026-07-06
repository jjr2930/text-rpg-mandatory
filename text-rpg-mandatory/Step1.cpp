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

CharacterGenerationScreen::CharacterGenerationScreen()
    : name(L"")
    , stat(new int[static_cast<int>(StatType::Size)] { 0, 0, 0, 0 })
{
}

void CharacterGenerationScreen::Run()
{         
    cout << "===========================================" << endl;
    cout << "[ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "===========================================" << endl;

    cout << "용사의 이름을 입력해주세요: ";
    wcin >> name;
    cout << endl;

    cout << "HP와 MP를 입력해주세요: ";
    cin >> stat[static_cast<int>(StatType::HP)] >> stat[static_cast<int>(StatType::MP)];
    cout << endl;

    cout << "공격력과 방어력을 입력해주세요: ";
    cin >> stat[static_cast<int>(StatType::Attack)] >> stat[static_cast<int>(StatType::Defense)];
    cout << endl;


    cout << "===================================" << endl; 
    wcout << name << " 의 현재 능력치" << endl;
    cout << "===================================" << endl;
    cout << "HP: " << stat[static_cast<int>(StatType::HP)] 
        << "    MP: " << stat[static_cast<int>(StatType::MP)] << endl;
    cout << "공격력: " << stat[static_cast<int>(StatType::Attack)] 
        << "    방어력: " << stat[static_cast<int>(StatType::Defense)] << endl;
    cout << "===================================" << endl;

    cout << "계속하려면 아무 키나 누르세요..." << endl;
    cin.ignore();
    cin.get();
}
