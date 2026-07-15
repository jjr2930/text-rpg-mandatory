#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "EventParameter.h" 
#include "DropItemData.h"
#include "InventoryItem.h"
#include "VirtualDisplay.h"

class Position;
class FieldItem;
class Stat;
class InteractableObject;

class Player : public Component
{
public: 
    enum class CurrentInputMode
    {
        Ingame,
        Inventory,
        Inetraction,
    };
public:
    using Component::Component;
    Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void HandleEvent(shared_ptr<EventParameter> message) override;
    void TakeDamage(int damage);
    void AddItem(const FieldItem& fieldItemm);

    int GetLevel() const;
    int GetExp() const;
    int GetCurrentHelath() const;
    int GetMaxHp() const;
    int GetAttack() const;
    int GetDefense() const;
    int GetInventoryElementCount() const;
    int GetInventoryCursorIndex() const;

    const vector<InventoryItem>& GetInventory() const;

private:
    void AddItems(vector<DropItemData>& dropItems);
    void Attack();
    void Interact();
    void AddExp(int exp);
    bool HasItem(int tableKey, int* index) const;
    void AddItemQuantity(int tableKey, int quantity);

    void ProcessIngameModeInput(char inputChar);
    void ProcessInventoryModeInput(char inputChar);

private:
    shared_ptr<Position> playerPosition;
    shared_ptr<Stat> playerStat;
    shared_ptr<InteractableObject> currentInteractableObject;

    vector<InventoryItem> inventory;

    int playerLevel;
    int currentExp;
    int maxExp;
    int inventoryCursorIndex = 0;
    int npcDialogCursorIndex = 0;

    CurrentInputMode currentInputMode;
};

#endif