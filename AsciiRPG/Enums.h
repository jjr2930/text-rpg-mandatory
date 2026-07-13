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
    /// <summary>
    /// 플레이어가 출구에 들어갔을 때 발생하는 이벤트
    /// </summary>
    OnPlayerEnteredExit,
    /// <summary>
    /// 맵 지우기 요청 이벤트
    /// 지우기 요청이라니 뭔가 애매함
    /// </summary>
    OnMapClearRequested,
    /// <summary>
    /// 입구에 도착했을 때 발생하는 이벤트
    /// </summary>
    OnPlayerEnteredEntrance,

};
#endif // !ENUMS_H

