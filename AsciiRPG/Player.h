#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>

#include "Component.h"
#include "EventParameter.h" 
#include "DropItemData.h"
#include "InventoryItem.h"
#include "VirtualDisplay.h"

class Position;
class FieldItem;
class Stat;
class InteractableObject;
class MonsterItemDropData;
class InventoryItem;

class Player : public Component
{
public: 
    enum class CurrentInputMode
    {
        Ingame,
        Inventory,
        Interaction,
    };

    constexpr static int DISPLAY_INVENTORY_COUNT_PER_PAGE = 10;

public:
    using Component::Component;
    Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void HandleEvent(shared_ptr<EventParameter> message) override;
    void TakeDamage(int damage);
    void AddItem(const FieldItem& fieldItemm);
    void AddItemQuantity(int tableKey, ItemType itemType, int quantity);
    void SetItemQuantity(int tableKey, ItemType, int quantity);
    void RemoveItemFromInventory(int tableKey, ItemType itemType);
    void EquipItem(int tableKey, ItemType itemType);

    int GetLevel() const;
    int GetExp() const;
    int GetCurrentHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetDefense() const;
    int GetInventoryElementCount() const;
    int GetInventoryCursorIndex() const;

    float GetAddedStat(StatType statType) const;
    float GetTotalStat(StatType statType) const;
    
    const vector<string> GetInventoryRenderStrings() const;
    const vector<InventoryItem>& GetInventory() const;
    const unordered_map<GearSlotType, InventoryItem>& GetEquippedGear() const;

    bool HasEnoughItem(int tableKey,ItemType itemType, int quantity) const;
    CurrentInputMode GetCurrentInputMode() const;

private:
    bool HasItem(int tableKey, ItemType itemType, int* index) const;
    void AddItems(shared_ptr<MonsterItemDropData> dropItem);
    void Attack();
    void Interact();
    void AddExp(int exp);
    int GetInventoryMinIndexForCurrentPage() const;
    int GetInventoryMaxIndexForCurrentPage() const;
    void ProcessIngameModeInput(Virtualkey inputKey);
    void ProcessInventoryModeInput(Virtualkey inputKey);

private:
    shared_ptr<Position> playerPosition;
    shared_ptr<Stat> playerStat;
    shared_ptr<InteractableObject> currentInteractableObject;

    vector<InventoryItem> inventory;
    unordered_map<GearSlotType, InventoryItem> equippedGear;

    int playerLevel;
    int maxExp;
    int inventoryCursorIndex = 0;
    int npcDialogCursorIndex = 0;
    int inventoryPageIndex = 0;

    bool amIDead = false;
    CurrentInputMode currentInputMode;
};

#endif