#pragma once
#include "Component.h"
#include "DropItemData.h"
#include "DateTime.h"

class Position;

class Monster : public Component
{
public:
    class MonsterConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        MonsterConstructionParameter(shared_ptr<Entity> entity, int hp, int attack, int defense, int exp, int attackDelay, const vector<DropItemData>& dropItems)
            : Component::ConstructionParamterBase(entity)
            , hp(hp)
            , attack(attack)
            , defense(defense)
            , exp(exp)
            , attackDelay(attackDelay)
            , dropItems(dropItems)
        {
        }
        vector<DropItemData> dropItems;
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
    vector<DropItemData>& GetDropItems();

    void Update() override;

private:
    int hp;
    int attack;
    int defense;
    int exp;
    bool fistOverlap;
    DateTime nextAttackTime;

    vector<DropItemData> dropItems;

    shared_ptr<Position> monsterPosition;    
};

