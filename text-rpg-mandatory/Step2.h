#ifndef STEP2_H
#define STEP2_H
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

namespace Step2 {
    enum class StatType {
        HP = 0,
        MP,
        Attack,
        Defense,
        Size
    };

    class CharacterGenerationScreen
    {
    public:
        CharacterGenerationScreen();
        void Run();
        void printStatus(std::wstring name, int stat[]);

    private:
        std::wstring name;
        int* stat;
    };
}

#endif // STEP2_H