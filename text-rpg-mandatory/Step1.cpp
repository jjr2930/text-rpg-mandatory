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
    , hp(0)
    , mp(0)
    , attack(0)
    , defense(0)
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
    cin >> hp >> mp;
    cout << endl;

    cout << "공격력과 방어력을 입력해주세요: ";
    cin >> attack >> defense;
    cout << endl;


    cout << "===================================" << endl; 
    wcout << name << " 의 현재 능력치" << endl;
    cout << "===================================" << endl;
    cout << "HP: " << hp << "    MP: " << mp << endl;
    cout << "공격력: " << attack << "    방어력: " << defense << endl;
    cout << "===================================" << endl;

    cout << "계속하려면 아무 키나 누르세요..." << endl;
    cin.ignore();
    cin.get();
}
