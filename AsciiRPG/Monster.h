#pragma once
#include "Component.h"
#include "DropItemData.h"

class Monster : public Component
{
public:
    class MonsterConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        MonsterConstructionParameter(shared_ptr<Entity> entity, int hp, int attack, int defense, int exp, const vector<DropItemData>& dropItems)
            : Component::ConstructionParamterBase(entity)
            , hp(hp)
            , attack(attack)
            , defense(defense)
            , exp(exp)
            , dropItems(dropItems)
        {
        }

        vector<DropItemData> dropItems;
        int hp;
        int attack;
        int defense;
        int exp;
    };

public:
    using Component::Component;
    Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void TakeDamage(int damage);
    int GetExp() const;
    bool IsDead() const;
    vector<DropItemData>& GetDropItems();

private:
    int hp;
    int attack;
    int defense;
    int exp;
    vector<DropItemData> dropItems;
};

