#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>

/*
- [ ]  `Monster` 클래스 만들기
- [ ]  `name`, `hp`, `power`, `defence`, `dropItemName`, `dropItemPrice` 멤버 변수 선언하기
- [ ]  기본 몬스터 예시: 슬라임 HP 30, 공격력 20, 방어력 10
- [ ]  `Monster::attack(Player* player)` 구현하기
- [ ]  `Player`에 전투에 필요한 getter/setter 추가하기: `getHP()`, `setHP()`, `getPower()`, `getDefence()` 등
- [ ]  데미지 공식: `공격력 - 방어력`
- [ ]  데미지가 0 이하이면 1로 고정하기
- [ ]  `while(player->getHP() > 0 && monster.getHP() > 0)` 전투 루프 작성하기
- [ ]  승리/패배 판정 메시지 출력하기

**주의할 점**

- STEP 4의 `attack()`은 "공격 메시지 출력" 역할로 두고, 실제 데미지 계산은 전투 함수에서 처리해도 됩니다.
- 몬스터 HP가 음수가 되어도 전투 종료 판정은 `<= 0`으로 처리하세요.
*/
class MonsterDropItem
{
public:
    MonsterDropItem(std::string& name, int price);

private:
    std::string dropItemName;
    int dropItemPrice;
};

class Monster
{
public:
    Monster(std::string& name, int hp, int power, int defence);
    virtual ~Monster() = default;
    virtual void Attack(class Player* player) = 0;
    void Damage(int damage, int* outRealDamage);

    std::string GetName() const;
    int GetHp() const;
    int GetPower() const;
    int GetDefence() const;

protected:
    std::string name;
    int hp;
    int power;
    int defence;
    std::vector<MonsterDropItem> dropItems;
};

#endif