#ifndef ENUMS_H
#define ENUMS_H

#include "Const.h"

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
    AttackDelay,
    Exp,


    AddedMaxHealth,
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
    Craft,
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
    q, w, e, r, t, y, u, i, o, p, a, s, d, f, g, h, j, k, l, z, x, c, v, b, n, m,
    Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M,
    
    Space,
    Up,
    Left,
    Right,
    Down,
    Escape,
    Backspace,
};

enum class DungeonTagTypes
{
    None = -1,
    Wall,
    Entrance,
    Exit,
    Player,
    Alchemist,
    FieldDropItem,
    GreenSlime,
    SekeletonWarrior,
    ForestGolblin,
    MoonlitWisp,
    CaveTroll,
    OgreBrute,
    StoneGolem,
    HarpyScout,
    VenomousSpider,
    SunCultAcolyte,
    SylphGuardian,
    AncientWyvertn,
    RedDragon,  //boss
};

enum class ItemType
{
    None = -1,
    Consumable,
    Ingredient,
    Gear,
};

enum class GearSlotType
{
    None = -1,
    Weapon,
    Head,
    Body,
    Feet,
    Accessory
};

class EnumUtility
{
public:
    static const int ToKeyCode(Virtualkey key)
    {
        switch (key)
        {
            case Virtualkey::Up: return Const::Key::Up;
            case Virtualkey::Left: return Const::Key::Left;
            case Virtualkey::Right: return Const::Key::Right;
            case Virtualkey::Down: return Const::Key::Down;
            case Virtualkey::Escape: return Const::Key::ESCAPE;
            case Virtualkey::Backspace: return Const::Key::BACKSPACE;
            case Virtualkey::Space: return (int)' ';

            case Virtualkey::A: return (int)'A';
            case Virtualkey::B: return (int)'B';
            case Virtualkey::C: return (int)'C';
            case Virtualkey::D: return (int)'D';
            case Virtualkey::E: return (int)'E';
            case Virtualkey::F: return (int)'F';
            case Virtualkey::G: return (int)'G';
            case Virtualkey::H: return (int)'H';
            case Virtualkey::I: return (int)'I';
            case Virtualkey::J: return (int)'J';
            case Virtualkey::K: return (int)'K';
            case Virtualkey::L: return (int)'L';
            case Virtualkey::M: return (int)'M';
            case Virtualkey::N: return (int)'N';
            case Virtualkey::O: return (int)'O';
            case Virtualkey::P: return (int)'P';
            case Virtualkey::Q: return (int)'Q';
            case Virtualkey::R: return (int)'R';
            case Virtualkey::S: return (int)'S';
            case Virtualkey::T: return (int)'T';
            case Virtualkey::U: return (int)'U';
            case Virtualkey::V: return (int)'V';
            case Virtualkey::W: return (int)'W';
            case Virtualkey::X: return (int)'X';
            case Virtualkey::Y: return (int)'Y';
            case Virtualkey::Z: return (int)'Z';

            case Virtualkey::a: return (int)'a';
            case Virtualkey::b: return (int)'b';
            case Virtualkey::c: return (int)'c';
            case Virtualkey::d: return (int)'d';
            case Virtualkey::e: return (int)'e';
            case Virtualkey::f: return (int)'f';
            case Virtualkey::g: return (int)'g';
            case Virtualkey::h: return (int)'h';
            case Virtualkey::i: return (int)'i';
            case Virtualkey::j: return (int)'j';
            case Virtualkey::k: return (int)'k';
            case Virtualkey::l: return (int)'l';
            case Virtualkey::m: return (int)'m';
            case Virtualkey::n: return (int)'n';
            case Virtualkey::o: return (int)'o';
            case Virtualkey::p: return (int)'p';
            case Virtualkey::q: return (int)'q';
            case Virtualkey::r: return (int)'r';
            case Virtualkey::s: return (int)'s';
            case Virtualkey::t: return (int)'t';
            case Virtualkey::u: return (int)'u';
            case Virtualkey::v: return (int)'v';
            case Virtualkey::w: return (int)'w';
            case Virtualkey::x: return (int)'x';
            case Virtualkey::y: return (int)'y';
            case Virtualkey::z: return (int)'z';

            default: return -1; // Return -1 for unsupported keys
        }
    }

    /// <summary>
    /// TODO: char* -> string
    /// </summary>
    /// <param name="statType"></param>
    /// <returns></returns>
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

    /// <summary>
    /// TODO: char* -> string
    /// </summary>
    /// <param name="operatorType"></param>
    /// <returns></returns>
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

    static const char ToChar(DungeonTagTypes tag)
    {
        switch (tag)
        {
            case DungeonTagTypes::None:             return ' ';
            case DungeonTagTypes::Wall:             return '#';
            case DungeonTagTypes::Entrance:         return 'S';
            case DungeonTagTypes::Exit:             return 'X';
            case DungeonTagTypes::Player:           return 'P';
            case DungeonTagTypes::Alchemist:        return 'N';
            case DungeonTagTypes::FieldDropItem:    return '*';
            case DungeonTagTypes::GreenSlime:       return 'L';
            case DungeonTagTypes::SekeletonWarrior: return 'K';
            case DungeonTagTypes::ForestGolblin:    return 'G';
            case DungeonTagTypes::MoonlitWisp:      return 'W';
            case DungeonTagTypes::CaveTroll:        return 'T';
            case DungeonTagTypes::OgreBrute:        return 'O';
            case DungeonTagTypes::StoneGolem:       return 'M';
            case DungeonTagTypes::HarpyScout:       return 'H';
            case DungeonTagTypes::VenomousSpider:   return 'I';
            case DungeonTagTypes::SunCultAcolyte:   return 'A';
            case DungeonTagTypes::SylphGuardian:    return 'Y';
            case DungeonTagTypes::AncientWyvertn:   return 'V';
            case DungeonTagTypes::RedDragon:        return 'D';
            default: return '?';
        }
    }

    static const DungeonTagTypes ToDungeonTagTypes(char c)
    {
        switch (c)
        {
            case ' ': return DungeonTagTypes::None;
            case '#': return DungeonTagTypes::Wall;
            case 'S': return DungeonTagTypes::Entrance;
            case 'X': return DungeonTagTypes::Exit;
            case 'P': return DungeonTagTypes::Player;
            case 'N': return DungeonTagTypes::Alchemist;
            case '*': return DungeonTagTypes::FieldDropItem;
            case 'L': return DungeonTagTypes::GreenSlime;
            case 'K': return DungeonTagTypes::SekeletonWarrior;
            case 'G': return DungeonTagTypes::ForestGolblin;
            case 'W': return DungeonTagTypes::MoonlitWisp;
            case 'T': return DungeonTagTypes::CaveTroll;
            case 'O': return DungeonTagTypes::OgreBrute;
            case 'M': return DungeonTagTypes::StoneGolem;
            case 'H': return DungeonTagTypes::HarpyScout;
            case 'I': return DungeonTagTypes::VenomousSpider;
            case 'A': return DungeonTagTypes::SunCultAcolyte;
            case 'Y': return DungeonTagTypes::SylphGuardian;
            case 'V': return DungeonTagTypes::AncientWyvertn;
            case 'D': return DungeonTagTypes::RedDragon; //boss
            default: return DungeonTagTypes::None; // Unknown character
        }
    }
};

#include "json.hpp"
NLOHMANN_JSON_SERIALIZE_ENUM(OperatorType, {
    {OperatorType::None, "None"},
    {OperatorType::Add, "Add"},
    {OperatorType::Subtract, "Subtract"},
    {OperatorType::Multiply, "Multiply"},
    {OperatorType::Divide, "Divide"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(StatType, {
    {StatType::None, "None"},
    {StatType::MaxHealth, "MaxHealth"},
    {StatType::CurrentHealth, "CurrentHealth"},
    {StatType::Attack, "Attack"},
    {StatType::Defense, "Defense"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(ItemType, {
    {ItemType::None, "None"},
    {ItemType::Consumable, "Consumable"},
    {ItemType::Ingredient, "Ingredient"},
    {ItemType::Gear, "Gear"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(GearSlotType, {
    {GearSlotType::None, "None"},
    {GearSlotType::Weapon, "Weapon"},
    {GearSlotType::Head, "Head" },
    {GearSlotType::Body, "Body" },
    {GearSlotType::Feet, "Feet" },
    {GearSlotType::Accessory, "Accessory" }
})
#endif // !ENUMS_H