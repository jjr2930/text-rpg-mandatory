#ifndef CONST_H
#define CONST_H

namespace Const
{
    namespace Map
    {
        constexpr int DEFAULT_WIDTH = 40;
        constexpr int DEFAULT_HEIGHT = 20;
        constexpr int GENERATION_STEP_MIN = 1000;
        constexpr int GENERATION_STEP_MAX = 1500;
        constexpr int DUNGEON_DEPTH = 10;

        constexpr char WALL = '#';
        constexpr char START = 'S';
        constexpr char EXIT = 'X';
        constexpr char ITEM = '*';
        constexpr char MONSTER = 'M';
        constexpr char EMPTY = ' ';
        constexpr char PLAYER = 'P';
        constexpr char NPC = 'N';
    }

    namespace Stat
    {
        namespace Player
        {
            static constexpr float INIT_HP = 100;
            static constexpr float INIT_ATTACK = 10;
            static constexpr float INIT_DEFENSE = 5;
        }
    }

}

#endif
