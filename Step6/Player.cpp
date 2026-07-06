#include "Player.h"
#include "Enums.h"
#include "Const.h"
#include <iostream>
#include <cassert>

using namespace std;

Player::Player(std::string& name, int* stats)
    : name(name)
    , job(JobType::Warrior)
    , level(Const::PLAYER::START_LEVEL)
    , hp(stats[(int)(StatType::HP)])
    , mp(stats[(int)(StatType::MP)])
    , power(stats[(int)(StatType::Attack)])
    , defence(stats[(int)(StatType::Defense)])
{
}

Player::~Player()
{
}

/*
------------------------------------
닉네임: 철수 | 직업: 마법사 | Lv.1
HP: 80 | MP: 90 | 공격력: 40 | 방어력: 25
------------------------------------
*/
void Player::PrintPlayerStatus()
{
    cout << "------------------------------------" << endl;
    cout << "닉네임: " << name << " | 직업: " << GetJobName() << " | Lv." << level << endl;
    cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << power << " | 방어력: " << defence << endl;
    cout << "------------------------------------" << endl;
}

void Player::Damage(int damage, int* realDamage)
{
    assert(damage >= 0);
    
    *realDamage = damage - defence;
    *realDamage = (*realDamage <= 0) ? 0 : *realDamage;

    hp -= *realDamage;

    cout << name << "이(가) " << *realDamage << " 데미지를 입었습니다. (남은 HP: " << hp << ")" << endl;
}

void Player::AddItem(Item& item)
{
    if (inventory.size() >= Const::PLAYER::INVENTORY_CAPACITY)
    {
        cout << "인벤토리가 가득 찼습니다. 아이템을 추가할 수 없습니다." << endl;
        return;
    }

    inventory.emplace_back(item);
}

/*
선택: 2
[ 인벤토리 (1/10) ]
1. 슬라임의 끈적한 젤리 (30G)
*/
void Player::PrintInventory()
{

    cout << "[ 인벤토리 (" << inventory.size() << "/" << Const::PLAYER::INVENTORY_CAPACITY << ") ]" << endl;
    
    int size = inventory.size();
    for (int i = 0; i < size; ++i)
    {
        cout << i + 1 << ". " << inventory[i].GetName() << " (" << inventory[i].GetPrice() << "G)" << endl;
    }
}

std::string& Player::GetName()
{
    return name;
}

JobType Player::GetJob()
{
    return job;
}

int Player::GetLevel()
{
    return level;
}

int Player::GetHp()
{
    return hp;
}

int Player::GetMp()
{
    return mp;
}

int Player::GetPower()
{
    return power;
}

int Player::GetDefence()
{
    return defence;
}

void Player::SetName(const std::string& name)
{
    this->name = name;
}

void Player::SetJob(JobType job)
{
    this->job = job;
}

void Player::SetLevel(int level)
{
    assert(level > 0);
    
    this->level = level;
}

void Player::SetHp(int hp)
{
    assert(hp >= 0);

    this->hp = hp;
}

void Player::SetMp(int mp)
{
    assert(mp >= 0);

    this->mp = mp;
}

void Player::SetPower(int power)
{
    assert(power >= 0);

    this->power = power;
}

void Player::SetDefence(int defence)
{
    assert(defence >= 0);

    this->defence = defence;
}

std::string Player::GetJobName()
{
    switch (job)
    {
        case JobType::Warrior:  return "전사";
        case JobType::Magician: return "마법사";
        case JobType::Thief:    return "도적";
        case JobType::Archer:   return "궁수";
        default:
            break;
    }

    return "알 수 없음";
}
