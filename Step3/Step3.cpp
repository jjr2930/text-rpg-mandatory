#include "Step3.h"
#include "Const.h"
#include <iostream>

using namespace std;
/*
HP 포션 5개, MP 포션 5개가 기본 지급되었습니다.
============================================
< 캐릭터 강화 >
1. HP UP    2. MP UP    3. 공격력 2배
4. 방어력 2배  5. 현재 능력치  0. 게임 시작
============================================
번호를 선택해주세요: 1
* HP가 20 증가했습니다. (HP 포션 차감: 남은 포션 4개)
번호를 선택해주세요: 0
게임을 시작합니다!
*/

Step3::CharacterUpgradeScreen::CharacterUpgradeScreen()
    : isGameStart(false)
    , hpPotionCount(Const::INITIAL_HP_POTION_COUNT)
    , mpPotionCount(Const::INITIAL_MP_POTION_COUNT)
{
    cout << "HP 포션 " << hpPotionCount << "개, MP 포션 " << mpPotionCount << "개가 기본 지급되었습니다." << endl;
}

void Step3::CharacterUpgradeScreen::Run(Step3::Menu& menu)
{
    bool loop = true;

    while (loop)
    {                           
        cout << "============================================" << endl;
        cout << "< 캐릭터 강화 >" << endl;
        cout << "1. HP UP    2. MP UP    3. 공격력 2배" << endl;
        cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;
        cout << "============================================" << endl;
        cout << "번호를 선택해주세요: ";
        int menuNumber = 0;
        cin >> menuNumber;
        cout << endl;

        switch (menuNumber)
        {
            case (int)UpgradeType::HP:
                if (hpPotionCount == 0)
                {
                    cout << "HP 포션이 없습니다." << endl;
                    break;
                }

                hpPotionCount--;
                menu.UpgradeHP();
                cout << "(HP 포션 차감: 남은 포션 " << hpPotionCount << "개)" << endl;
                break;

            case (int)UpgradeType::MP:
                if (mpPotionCount == 0)
                {
                    cout << "MP 포션이 없습니다." << endl;
                    break;
                }

                mpPotionCount--;
                menu.UpgradeMP();
                cout << "(MP 포션 차감: 남은 포션 " << mpPotionCount << "개)" << endl;
                break;

            case (int)UpgradeType::Attack:
                menu.UpgradeAttack();
                break;

            case (int)UpgradeType::Defense:
                menu.UpgradeDefense();
                break;

            case (int)UpgradeType::PrintStatus:
                menu.PrintStatusUsingSelf();
                break;

            case (int)UpgradeType::GameStart:
                cout << "게임 시작" << endl;
                loop = false;
                break;

            default:
                break;
        }
    }
}
                                                      

Step3::Menu::Menu()
    : name(L"")
    , stat(new int[(int)(Step3::StatType::Size)] { 0, 0, 0, 0 })
{
}

void Step3::Menu::Run()
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
}

void Step3::Menu::PrintStatus(std::wstring name, int* stat)
{
    cout << "===================================" << endl; 
    wcout << name << " 의 현재 능력치" << endl;
    cout << "===================================" << endl;
    cout << "HP: " << stat[(int)(Step3::StatType::HP)] 
        << "    MP: " << stat[(int)(Step3::StatType::MP)] << endl;
    cout << "공격력: " << stat[(int)(Step3::StatType::Attack)] 
        << "    방어력: " << stat[(int)(Step3::StatType::Defense)] << endl;
    cout << "===================================" << endl;                                                                            
}

void Step3::Menu::UpgradeHP()
{
    stat[(int)(Step3::StatType::HP)] += Const::HP_INCREASE_AMOUNT;
    cout << "* HP가 " << Const::HP_INCREASE_AMOUNT << " 증가했습니다. ";
}

void Step3::Menu::UpgradeMP()
{
    stat[(int)(Step3::StatType::MP)] += Const::MP_INCREASE_AMOUNT;
    cout << "* MP가 " << Const::MP_INCREASE_AMOUNT << " 증가했습니다. ";
}

void Step3::Menu::UpgradeAttack()
{
    stat[(int)(Step3::StatType::Attack)] *= 2;
}

void Step3::Menu::UpgradeDefense()
{
    stat[(int)(Step3::StatType::Defense)] *= 2;
}

void Step3::Menu::PrintStatusUsingSelf()
{
    PrintStatus(name, stat);
}
