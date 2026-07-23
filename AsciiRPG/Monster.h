#ifndef MONSTER_H
#define MONSTER_H

#include "Component.h"
#include "DateTime.h"
#include "MonsterTable.h"
#include "MonsterItemDropTable.h"

class Position;
class Stat;

class Monster : public Component
{
public:
    class MonsterConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        MonsterConstructionParameter(shared_ptr<Entity> entity, int dropTableKey)
            : Component::ConstructionParamterBase(entity)
            , dropTableKey(dropTableKey)
        {
        }
        int dropTableKey;
    };

public:
    using Component::Component;
    Monster(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    virtual ~Monster() = default;

    void TakeDamage(int damage);
    int GetExp() const;
    bool IsDead() const;
    shared_ptr<MonsterItemDropData> RollDropTable() const;

    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;

protected:
    vector<shared_ptr<MonsterItemDropData>> dropItems;
    shared_ptr<Position> monsterPosition;    
    shared_ptr<Stat> monsterStat;
};

#endif