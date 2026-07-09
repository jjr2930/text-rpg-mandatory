#pragma once
#include "Component.h"
#include "EventParameter.h" 
#include "DropItemData.h"
#include "InventoryItem.h"

class Position;

class Player : public Component
{
public:
    class PlayerConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        PlayerConstructionParameter(shared_ptr<Entity> entity, int initHp, int attack, int defense)
            : Component::ConstructionParamterBase(entity)
            , initHp(initHp)
            , attack(attack)
            , defense(defense)
        {}

        int initHp;
        int attack;
        int defense;
    };
public:
    using Component::Component;
    Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
    void Attack();
    void AddItems(vector<DropItemData>& dropItems);
    void AddExp(int exp);

private:
    shared_ptr<Position> playerPosition;
    vector<InventoryItem> inventory;

    int initHp;
    int attack;
    int defense;
    int playerLevel;
    int currentExp;
};

