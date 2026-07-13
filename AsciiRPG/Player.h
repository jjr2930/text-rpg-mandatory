#pragma once
#include "Component.h"
#include "EventParameter.h" 
#include "DropItemData.h"
#include "InventoryItem.h"
#include "VirtualDisplay.h"

class Position;
class FieldItem;

class Player : public Component
{
public: 
    enum class CurrentInputMode
    {
        Ingame,
        Inventory
    };
    static constexpr int INIT_HP = 100;
    static constexpr int INIT_ATTACK = 10;
    static constexpr int INIT_DEFENSE = 5;

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
    void TakeDamage(int damage);
    void AddItem(const FieldItem& fieldItemm);

    int GetLevel() const;
    int GetExp() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetAttack() const;
    int GetDefense() const;
    int GetInventoryElementCount() const;
    int GetInventoryCursorIndex() const;

    const vector<InventoryItem>& GetInventory() const;

private:
    void AddItems(vector<DropItemData>& dropItems);
    void Attack();
    void AddExp(int exp);
    bool HasItem(const string& itemName, int* index) const;

    void ProcessIngameModeInput(char inputChar);
    void ProcessInventoryModeInput(char inputChar);

private:
    shared_ptr<Position> playerPosition;
    vector<InventoryItem> inventory;

    int maxHp;
    int currentHp;
    int attack;
    int defense;
    int playerLevel;
    int currentExp;
    int maxExp;
    int inventoryCursorIndex = 0;

    CurrentInputMode currentInputMode;
};

