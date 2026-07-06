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

namespace Step1 {
    enum class StatType {
        HP = 0,
        MP,
        Attack,
        Defense,
        Size
    };

    class Menu
    {
    public:
        Menu();
        void Run();
        void PrintStatus(std::wstring name, int stat[]);

    private:
        std::wstring name;
        int* stat;
    };
}

#endif // STEP1_H