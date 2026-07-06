#ifndef ENUMS_H
#define ENUMS_H

enum class JobType {
    None = 0,
    Warrior = 1,
    Magician,
    Thief,
    Archer
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

enum class MenuSelectionType {
    ExitGame        = 0,
    EnterDungeon    = 1,
    PrintInventory  = 2 ,
};

#endif
