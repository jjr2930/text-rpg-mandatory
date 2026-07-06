#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "Enums.h"
#include "Item.h"

/*
- [ ]  `Player` 클래스 만들기
- [ ]  `protected` 멤버 변수로 `name`, `job`, `level`, `hp`, `mp`, `power`, `defence` 선언하기
- [ ]  이전 STEP의 `name`, `stat[]` 값을 `Player` 생성자로 넘기기
- [ ]  생성자 예시: `Player(string name, int hp, int mp, int power, int defence)`
- [ ]  getter/setter, `printPlayerStatus()` 작성하기
- [ ]  `Player`에 `virtual void attack() = 0` 순수 가상함수 추가하기
- [ ]  `Player`에 `virtual ~Player() {}` 가상 소멸자 추가하기
- [ ]  `Warrior`, `Magician`, `Thief`, `Archer` 클래스가 `Player`를 상속하도록 만들기
- [ ]  직업별 특화 스탯 하나를 +30 하기
- [ ]  직업별 `attack()` 메시지를 다르게 오버라이딩하기
- [ ]  `main`에서 `Player* player = nullptr` 선언 후 직업 선택에 따라 동적 할당하기
- [ ]  프로그램 종료 전 `delete player` 호출하기
- [ ]  가능하다면 `Player.h`, `Player.cpp`, `Warrior.h`, `Warrior.cpp`처럼 헤더/소스 파일을 나누어보기

**주의할 점**
*/

class Monster;

class Player
{
public:
    Player(std::string& name, int* stats);
    virtual ~Player();

    void PrintPlayerStatus();
    void Damage(int damage, int* realDamage);
    void AddItem(Item& item);
    void PrintInventory();
/*
* Getters
*/
    std::string&    GetName();
    JobType         GetJob();
    int             GetLevel();
    int             GetHp();
    int             GetMp();
    int             GetPower();
    int             GetDefence();

/*
* Setters
*/
    void SetName(const std::string& name);
    void SetJob(JobType job);
    void SetLevel(int level);
    void SetHp(int hp);
    void SetMp(int mp);
    void SetPower(int power);
    void SetDefence(int defence);
    

    virtual void Attack() = 0;
    virtual void Attack(Monster* monster) = 0;

protected:
#pragma region UTILITY METHODS
    std::string GetJobName();
#pragma endregion


protected:
    std::string name;
    JobType job;
    int level;
    int hp;
    int mp;
    int power;
    int defence;

    std::vector<Item> inventory;
};

#endif