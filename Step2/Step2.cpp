#include "Step2.h"
#include "Const.h"

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

Step2::Menu::Menu()
    : name(L"")
    , stat(new int[(int)(Step2::StatType::Size)] { 0, 0, 0, 0 })
{
}

void Step2::Menu::Run()
{         
    cout << "===========================================" << endl;
    cout << "[ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "===========================================" << endl;

    cout << "용사의 이름을 입력해주세요: ";
    getline(wcin, name) ;
    cout << endl;

    while (true)
    {
        cout << "HP와 MP를 입력해주세요: ";
        cin >> stat[(int)(StatType::HP)] >> stat[(int)(StatType::MP)];
        cout << endl;

        if(stat[(int)(StatType::HP)] > Const::MIN_STAT && stat[(int)(StatType::MP)] > Const::MIN_STAT)
        {
            break;
        }
        else
        {
            cout << "HP와 MP는 최소 " << Const::MIN_STAT << " 초과해야 합니다." << endl;
        }
    }
    cout << "공격력과 방어력을 입력해주세요: ";

    while (true)
    {
        cin >> stat[(int)(StatType::Attack)] >> stat[(int)(StatType::Defense)];
        cout << endl;
        if (stat[(int)(StatType::Attack)] > Const::MIN_STAT && stat[(int)(StatType::Defense)] > Const::MIN_STAT)
        {
            break;
        }
        else
        {
            cout << "공격력과 방어력은 최소 " << Const::MIN_STAT << " 초과해야 합니다." << endl;
        }
    }

    cout << endl;

    PrintStatus(name, stat);

    cin.ignore();
    cin.get();
}

void Step2::Menu::PrintStatus(std::wstring name, int stat[])
{
    cout << "===================================" << endl; 
    wcout << name << " 의 현재 능력치" << endl;
    cout << "===================================" << endl;
    cout << "HP: " << stat[(int)(Step2::StatType::HP)] 
        << "    MP: " << stat[(int)(Step2::StatType::MP)] << endl;
    cout << "공격력: " << stat[(int)(Step2::StatType::Attack)] 
        << "    방어력: " << stat[(int)(Step2::StatType::Defense)] << endl;
    cout << "===================================" << endl;

    cout << "계속하려면 아무 키나 누르세요..." << endl;                                                                                      
}
