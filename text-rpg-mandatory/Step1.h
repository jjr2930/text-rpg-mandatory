#ifndef STEP1_H
#define STEP1_H
#include <string>

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

class CharacterGenerationScreen 
{
public :
    CharacterGenerationScreen();
    void Run();


private:
    std::wstring name;
    int hp;
    int mp;
    int attack;
    int defense;
};
#endif // STEP1_H

