#ifndef MONSTER_H
#define MONSTER_H

#include "Component.h"
#include "DateTime.h"
#include "MonsterTable.h"
#include "MonsterItemDropTable.h"

class Position;

class Monster : public Component
{
public:
    class MonsterConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        MonsterConstructionParameter(shared_ptr<Entity> entity, int hp, int attack, int defense, int exp, int attackDelay, int dropTableKey)
            : Component::ConstructionParamterBase(entity)
            , hp(hp)
            , attack(attack)
            , defense(defense)
            , exp(exp)
            , attackDelay(attackDelay)
            , dropTableKey(dropTableKey)
        {
        }
        int dropTableKey;
        int hp;
        int attack;
        int defense;
        int exp;
        int attackDelay;
    };

public:
    using Component::Component;
    Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void TakeDamage(int damage);
    int GetExp() const;
    bool IsDead() const;
    vector<shared_ptr<MonsterItemDropData>>& GetDropItems();

    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
    int exp;
    bool fistOverlap;
    DateTime nextAttackTime;

    vector<shared_ptr<MonsterItemDropData>> dropItems;

    shared_ptr<Position> monsterPosition;    
    shared_ptr<Stat> monsterStat;
};

#endif