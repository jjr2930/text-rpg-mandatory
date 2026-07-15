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

    namespace Key
    {
        static constexpr int SPECIAL_KEY_PREFIX = -32; // Special key prefix for arrow keys and function keys
        static constexpr int BACKSPACE          = 8;
        static constexpr int ESCAPE                = 27;
        static constexpr int Up                 = 72;   
        static constexpr int Left               = 75;
        static constexpr int Right              = 77;
        static constexpr int Down               = 80;
    }
}

#endif
