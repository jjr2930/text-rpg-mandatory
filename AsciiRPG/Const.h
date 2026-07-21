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
        constexpr char DRAGON = 'D';
        constexpr char DRAGON_BULLET = 'B';
    }

    namespace Stat
    {
        namespace Player
        {
            static constexpr float INIT_HP = 100;
            static constexpr float INIT_ATTACK = 10;
            static constexpr float INIT_DEFENSE = 5;
        }

        namespace DRAGON
        {
            static constexpr float INIT_HP = 200;
            static constexpr float INIT_ATTACK = 15;
            static constexpr float INIT_DEFENSE = 10;
            static constexpr float MOVING_TIMEOUT = 5.0; // seconds
        }

        namespace DRAGON_BULLET
        {
            static constexpr float SPEED = 3.0;
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

    namespace ConsoleColor
    {
        static constexpr int BLACK = 0;
        static constexpr int BLUE = 1;
        static constexpr int GREEN = 2;
        static constexpr int CYAN = 3;
        static constexpr int RED = 4;
        static constexpr int MAGENTA = 5;
        static constexpr int YELLOW = 6;
        static constexpr int WHITE = 7;
        static constexpr int DEFAULT = 7;
        static constexpr int GRAY = 8;
        static constexpr int BRIGHT_BLUE = 9;
        static constexpr int BRIGHT_GREEN = 10;
        static constexpr int BRIGHT_CYAN = 11;
        static constexpr int BRIGHT_RED = 12;
        static constexpr int BRIGHT_MAGENTA = 13;
        static constexpr int BRIGHT_YELLOW = 14;
        static constexpr int BRIGHT_WHITE = 15;
    }
}

#endif
