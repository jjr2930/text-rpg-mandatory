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
    /// <summary>
    /// 어떤 오브젝트와 상호작용을 시작했을 때 발생하는 이벤트
    /// </summary>
    OnStartInteraction,   
    /// <summary>
    /// 상호작용 끝날때
    /// </summary>
    OnStopInteraction,
};

enum class StatType
{
    None = -1,
    MaxHealth,
    CurrentHealth,
    Attack,
    Defense,
};

enum class OperatorType
{
    None = -1,
    Add,
    Subtract,
    Multiply,
    Divide,
};

enum class AlchemyShopState
{
    None = -1,
    MainMenu = 0,
    RecipeList,
    FindRecipe,

};

enum class InteractableObjectTags
{
    None= -1,
    AlchemyShop = 0,
};

enum class RenderMode
{
    None = -1,
    Ingame = 0,
};

enum class Virtualkey
{
    None = -1,
    w,W,
    a,A,
    s,S,
    d,D,
    i,I,
    e,E,

    Space,
    Up,
    Left,
    Right,
    Down,
};

class EnumUtility
{
public:
    static const char* ToString(StatType statType)
    {
        switch (statType)
        {
            case StatType::None: return "None";
            case StatType::MaxHealth: return "MaxHealth";
            case StatType::CurrentHealth: return "CurrentHealth";
            case StatType::Attack: return "Attack";
            case StatType::Defense: return "Defense";
            default: return "Unknown";
        }
    }

    static const char* ToString(OperatorType operatorType)
    {
        switch (operatorType)
        {
            case OperatorType::None: return "None";
            case OperatorType::Add: return "Add";
            case OperatorType::Subtract: return "Subtract";
            case OperatorType::Multiply: return "Multiply";
            case OperatorType::Divide: return "Divide";
            default: return "Unknown";
        }
    }
};

#endif // !ENUMS_H