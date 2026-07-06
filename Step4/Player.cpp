#include "Player.h"
#include "Enums.h"
#include "Const.h"
#include <iostream>
#include <cassert>

using namespace std;

Player::Player(std::string& name, int* stats)
    : name(name)
    , job(JobType::Warrior)
    , level(Const::START_LEVEL)
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
}
