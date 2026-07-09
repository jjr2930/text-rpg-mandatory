#ifndef ENUMS_H
#define ENUMS_H

enum class MapCellType
{
    Normal,
    Entrance,
    Exit,
    Wall,
};

enum class Dicrection
{
    Up = 0,
    Down,
    Left,
    Right,
    Count,
};

enum class EventType
{
    KeyPressed,
};
#endif // !ENUMS_H

