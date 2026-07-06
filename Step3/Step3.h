#ifndef STEP3_H
#define STEP3_H
#include <string>

namespace Step3 {
    class Menu;

    class CharacterUpgradeScreen
    {
    public:
        CharacterUpgradeScreen();
        void Run(Step3::Menu& menu);

    private:
        bool isGameStart;
        int hpPotionCount;
        int mpPotionCount;
    };

    enum class StatType {
        HP = 0,
        MP,
        Attack,
        Defense,
        Size
    };

    enum class UpgradeType {
        GameStart = 0,
        HP = 1,
        MP,
        Attack,
        Defense,
        PrintStatus,
    };

    class Menu
    {
    public:
        Menu();
        void Run();
        void PrintStatus(std::wstring name, int* stat);
        void UpgradeHP();
        void UpgradeMP();
        void UpgradeAttack();
        void UpgradeDefense();
        void PrintStatusUsingSelf();

    private:
        std::wstring name;
        int* stat;
    };
}
#endif // !STEP3_H