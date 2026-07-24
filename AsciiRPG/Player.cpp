#include <format>
#include <cassert>

#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "Monster.h"
#include "MathUtility.h"
#include "Logger.h"
#include "FieldItem.h"
#include "LevelExpTable.h"
#include "Stat.h"
#include "Const.h"
#include "ItemBank.h"
#include "InteractableObject.h"
#include "MinMax.h"
#include "IItem.h"
#include "Enums.h"
#include "ConsumableItemTable.h"
#include "AlchemyTable.h"
#include "Dragon.h"
#include "GearTable.h"
#include "InventoryItem.h"

using namespace std;

Player::Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , playerLevel(1)
    , currentInputMode(CurrentInputMode::Ingame)
{
    inventoryCursorIndex = -1;
    maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);
   
    //auto townportal = ConsumableItemTable::GetInstance().GetData(2012);
    //AddItemQuantity(townportal->key, townportal->itemType, 10);

    if (auto ptr = entity.lock())
    {
        playerPosition = ptr->GetComponent<Position>();
        playerStat = ptr->GetComponent<Stat>();
    }
}

void Player::HandleEvent(shared_ptr<EventParameter> message)
{
    if (amIDead)
    {
        return;
    }

    switch (message->eventType)
    {
        case EventType::KeyPressed:
            {
                InputEventParameter* inputMessage = static_cast<InputEventParameter*>(message.get());
                Virtualkey inputKey = inputMessage->key;
                switch (currentInputMode)
                {
                    case CurrentInputMode::Ingame:
                        ProcessIngameModeInput(inputKey);
                        break;
                    case CurrentInputMode::Inventory:
                        ProcessInventoryModeInput(inputKey);
                        break;

                    case CurrentInputMode::Interaction:
                        //in this case, the input is handled by the current interactable object
                        break;
                    default:
                        break;
                }
            }
            break;

        case EventType::OnStopInteraction:
            {
                if (currentInputMode == CurrentInputMode::Interaction)
                {
                    currentInputMode = CurrentInputMode::Ingame;
                    currentInteractableObject->OnDisable();
                    currentInteractableObject = nullptr;
                }
            }
            break;

        default:
            break;
    }
}

void Player::TakeDamage(int damage)
{
    int defense = static_cast<int>(playerStat->GetStat(StatType::Defense));
    int realDamage = damage - defense;
    if (realDamage < 1)
        realDamage = 1;
    
    playerStat->AddStat(StatType::CurrentHealth, -realDamage);
    int currentHealth = static_cast<int>(playerStat->GetStat(StatType::CurrentHealth));
    if (currentHealth <= 0)
    {
        amIDead = true;
        Logger::LogInfo("Player is dead!");
    }
}

void Player::AddItem(const FieldItem& fieldItemm)
{
    int foundIdex;
    if (HasItem(fieldItemm.GetTableKey(), fieldItemm.GetItemType(), &foundIdex))
    {
        Logger::LogInfo(format("Player already has item: {0}", fieldItemm.GetTableKey()));
        inventory[foundIdex].AddQuantity(fieldItemm.GetQuantity());
    }
    else
    {
        InventoryItem newInventoryItem(fieldItemm.GetTableKey(), 
            fieldItemm.GetItemType(), 
            fieldItemm.GetQuantity());

        inventory.emplace_back(newInventoryItem);
    }
}

void Player::AddItemQuantity(int tableKey, ItemType itemType, int quantity)
{
    bool found = false;
    for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
    {
        if (iter->GetTableKey() == tableKey)
        {
            found = true;
            iter->AddQuantity(quantity);
            if (iter->GetQuantity() <= 0)
            {
                Logger::LogInfo(format("{0} removed", iter->GetName()));
                inventory.erase(iter);
            }
            else
            {
                Logger::LogInfo(format("{0} {1}", iter->GetName(), quantity));
            }
            return;
        }
    }

    if (!found && quantity > 0)
    {
        InventoryItem newItem(tableKey, itemType, quantity);
        inventory.emplace_back(newItem);

        Logger::LogInfo(format("Item {0} X{1} added"
            , newItem.GetName(), newItem.GetQuantity()));
    }

    inventoryCursorIndex = min(inventoryCursorIndex, (int)inventory.size() - 1);
}

void Player::SetItemQuantity(int tableKey, ItemType itemType, int quantity)
{
    int foundIndex;
    if (!HasItem(tableKey, itemType, &foundIndex))
    {
        Logger::LogInfo(format("Player does not have item: {0}", tableKey));
        return;
    }
    
    inventory[foundIndex].SetQuantity(quantity);

    if(inventory[foundIndex].GetQuantity() <= 0)
    {
        inventory.erase(inventory.begin() + foundIndex);
    }
}

void Player::RemoveItemFromInventory(int tableKey, ItemType itemType)
{
    for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
    {
        if (iter->GetTableKey() == tableKey && iter->GetItemType() == itemType)
        {
            inventory.erase(iter);
            break;
        }
    }
}

void Player::EquipItem(int tableKey, ItemType itemType)
{
    InventoryItem newItem(tableKey, itemType, 1);
    shared_ptr<IItem> item = ItemBank::GetInstance().GetItem(tableKey, itemType);
    shared_ptr<GearData> gearData = dynamic_pointer_cast<GearData>(item);
    assert(gearData && "Item is not a gear item");

    auto foundedIter = equippedGear.find(gearData->slot);
    if (foundedIter != equippedGear.end()) 
    {
        auto current = foundedIter->second;
        AddItemQuantity(current.GetTableKey(), current.GetItemType(), current.GetQuantity());
    }
    
    equippedGear.insert_or_assign(gearData->slot, newItem);

    float addedMaxHealth = GetAddedStat(StatType::MaxHealth);
    playerStat->SetStat(StatType::AddedMaxHealth, addedMaxHealth);
}

int Player::GetLevel() const
{
    return playerLevel;
}

int Player::GetExp() const
{
    return static_cast<int>(playerStat->GetStat(StatType::Exp));
}

int Player::GetCurrentHealth() const
{
    return static_cast<int>(playerStat->GetStat(StatType::CurrentHealth));
}

int Player::GetMaxHealth() const
{
    return static_cast<int>(playerStat->GetStat(StatType::MaxHealth));
}

int Player::GetAttack() const
{
    return static_cast<int>(playerStat->GetStat(StatType::Attack));
}

int Player::GetDefense() const
{
    return static_cast<int>(playerStat->GetStat(StatType::Defense));
}

int Player::GetInventoryElementCount() const
{
    return (int)inventory.size();
}

int Player::GetInventoryCursorIndex() const
{
    return inventoryCursorIndex;
}

float Player::GetAddedStat(StatType statType) const
{
    float totalStat = GetTotalStat(statType);
    float baseStat = playerStat->GetStat(statType);
    float addedStat = totalStat - baseStat;
    return addedStat;
}

float Player::GetTotalStat(StatType statType) const
{
    float result = playerStat->GetStat(statType);

    OperatorType operatorOrder[]
    {
        OperatorType::Add,
        OperatorType::Subtract,
        OperatorType::Multiply,
        OperatorType::Divide
    };

    for (auto& op : operatorOrder)
    {
        for (auto& gear : equippedGear)
        {
            auto itemData = ItemBank::GetInstance().GetItem(gear.second.GetTableKey(), gear.second.GetItemType());
            auto gearData = dynamic_pointer_cast<GearData>(itemData);
            assert(gearData && "Item is not a gear item");

            for (auto& statModifier : gearData->statModifiers)
            {
                if (statModifier->statType == statType && statModifier->operatorType == op)
                {
                    switch (op)
                    {
                        case OperatorType::Add:
                            result += statModifier->amount;
                            break;
                        case OperatorType::Subtract:
                            result -= statModifier->amount;
                            break;
                        case OperatorType::Multiply:
                            result *= statModifier->amount;
                            break;
                        case OperatorType::Divide:
                            assert(statModifier->amount != 0.0f && "Division by zero in GetStatFromGearWithOperator");
                            result /= statModifier->amount;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    return result;
}

const vector<string> Player::GetInventoryRenderStrings() const
{
    int minIndex = inventoryPageIndex * DISPLAY_INVENTORY_COUNT_PER_PAGE;
    int maxIndex = minIndex + DISPLAY_INVENTORY_COUNT_PER_PAGE - 1;
    maxIndex = min(maxIndex, (int)inventory.size() - 1);

    vector<string> renderStrings;
    for (int i = minIndex; i <= maxIndex; ++i)
    {
        const auto& item = inventory[i];
        string itemName = item.GetName();
        int quantity = item.GetQuantity();

        if (inventoryCursorIndex == i)
        {
            itemName = format(">{0} x{1}<", itemName, quantity);
        }
        else
        {
            itemName = format(" {0} x{1} ", itemName, quantity);
        }
        renderStrings.emplace_back(itemName);
    }

    if (currentInputMode == CurrentInputMode::Inventory)
    {
        int totalPages = (int)ceil((float)inventory.size() / DISPLAY_INVENTORY_COUNT_PER_PAGE);
        string pageInfo = format("Page {0}/{1}", inventoryPageIndex + 1, totalPages);
        renderStrings.emplace_back(pageInfo);

        renderStrings.emplace_back("Esc: exit inventory.");
        renderStrings.emplace_back("Up/Down: move cursor.");
        renderStrings.emplace_back("Left/Right: change page.");
    }
    return renderStrings;
}

const vector<InventoryItem>& Player::GetInventory() const
{
    return inventory;
}

const unordered_map<GearSlotType, InventoryItem>& Player::GetEquippedGear() const
{
    return equippedGear;
}

bool Player::HasEnoughItem(int tableKey, ItemType itemType, int quantity) const
{
    for (const auto& item : inventory)
    {
        if (item.GetTableKey() == tableKey && item.GetItemType() == itemType && item.GetQuantity() >= quantity)
        {
            return true;
        }
    }

    return false;
}

void Player::Attack()
{
    auto results = ObjectManager::GetInstance().GetComponentWithEntityTuppleVector<Monster, Position>();
    for (auto& [monsterEntity, monster, monsterPosition] : results)
    {
        Vector2Int position = playerPosition->GetPosition();
        Vector2Int monsterPos = monsterPosition->GetPosition();
        if (!MathUtility::IsOverlap(position, monsterPos, 1))
            continue;

        string monsterEntityName = "";
        Logger::LogInfo(format("player attack {}", monsterEntity->GetName()));

        monster->TakeDamage( this->GetTotalStat(StatType::Attack));
        if (monster->IsDead())
        {
            shared_ptr<MonsterItemDropData> dropItem = monster->RollDropTable();
            int exp = monster->GetExp();
            AddItems(dropItem);
            AddExp(exp);
        }
        break;
    }
}

void Player::Interact()
{
    auto components = ObjectManager::GetInstance().GetComponentTupleVector<InteractableObject, Position>();

    vector<shared_ptr<InteractableObject>> interactableObjectsInRange;
    interactableObjectsInRange.reserve(components.size());

    for (auto& [interactableObject, position] : components)
    {
        Vector2Int coords = position->GetPosition();
        if (!MathUtility::IsOverlap(playerPosition->GetPosition(), coords, 1))
            continue;

        interactableObjectsInRange.emplace_back(interactableObject);
    }

    if (interactableObjectsInRange.size() == 0)
    {
        Logger::LogInfo("No interactable objects in range.");
        return;
    }

    auto& interactableObject = interactableObjectsInRange[0];

    currentInteractableObject = interactableObject;
    currentInteractableObject->Reset();

    currentInputMode = CurrentInputMode::Interaction;

    ObjectManager::GetInstance().BroadcastEvent(make_shared<InteractionStartEventParameter>(interactableObject));
}

void Player::AddItems(shared_ptr<MonsterItemDropData> dropItem)
{
    if (nullptr == dropItem)
        return;

    int index;
    MinMaxInt minMaxQuantity(dropItem->minQuantity, dropItem->maxQuantity);
    int randomQuantity = minMaxQuantity.GetRandomValue();
        
    if (HasItem(dropItem->key, dropItem->itemType, &index))
    {
        inventory[index].AddQuantity(randomQuantity);
        Logger::LogInfo(format("{} x{} added", dropItem->key, randomQuantity));
    }
    else
    {
        InventoryItem newItem(dropItem->key, dropItem->itemType, randomQuantity);
        inventory.emplace_back(newItem);

        Logger::LogInfo(format("{} x{} added",
            newItem.GetName(), newItem.GetQuantity()));
    }
}

void Player::AddExp(int exp)
{
    playerStat->AddStat(StatType::Exp, static_cast<float>(exp));

    Logger::LogInfo(format("{} exp added", exp));
    
    float currentExp = playerStat->GetStat(StatType::Exp);
    if (currentExp >= maxExp)
    {
        playerLevel++;
        currentExp -= maxExp;
        playerStat->SetStat(StatType::Exp, currentExp);
        
        float fInitMaxHp = static_cast<float>(Const::Stat::Player::INIT_HP);
        float fInitAttack = static_cast<float>(Const::Stat::Player::INIT_ATTACK);
        float fInitDefense = static_cast<float>(Const::Stat::Player::INIT_DEFENSE);

        float r = 1.1f; 
        //복리 계산하기 (1+0.1)10−1
        float factor = pow(r, static_cast<float>(playerLevel - 1));
       
        float nextBaseMaxHealth = fInitMaxHp * factor;
        float nextAttack = fInitAttack * factor;
        float nextDefense = fInitDefense * factor;

        playerStat->SetStat(StatType::MaxHealth, nextBaseMaxHealth);
        playerStat->SetStat(StatType::Attack, nextAttack);
        playerStat->SetStat(StatType::Defense, nextDefense);        

        maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);
        Logger::LogInfo(format("level up!: {0}, maxHp -> {1}, atk -> {2}, def -> {3}",
            playerLevel, playerStat->GetStat(StatType::MaxHealth), 
            playerStat->GetStat(StatType::Attack), playerStat->GetStat(StatType::Defense)));
    }
}

Player::CurrentInputMode Player::GetCurrentInputMode() const
{
    return currentInputMode;
}

int Player::GetInventoryMinIndexForCurrentPage() const
{
    return inventoryPageIndex * DISPLAY_INVENTORY_COUNT_PER_PAGE;
}

int Player::GetInventoryMaxIndexForCurrentPage() const
{
    int max = GetInventoryMinIndexForCurrentPage() + DISPLAY_INVENTORY_COUNT_PER_PAGE - 1;
    max = min(max, (int)inventory.size() - 1);
    return max;
}

bool Player::HasItem(int tableKey, ItemType itemType, int* index) const
{
    int count = static_cast<int>(inventory.size());
    for (int i = 0; i < count; ++i)
    {
        if (inventory[i].GetTableKey() == tableKey
            && inventory[i].GetItemType() == itemType)
        {
            if (index)
            {
                *index = i;
            }
            return true;
        }
    }
    return false;
}

void Player::ProcessIngameModeInput(Virtualkey inputKey)
{
    switch (inputKey)
    {
        case Virtualkey::Up:
            playerPosition->TryMoveYOnly(-1);
            break;
                    
        case Virtualkey::Down:
            playerPosition->TryMoveYOnly(1);
            break;

        case Virtualkey::Left:
            playerPosition->TryMoveXOnly(-1);
            break;

        case Virtualkey::Right:
            playerPosition->TryMoveXOnly(1);
            break;

        case Virtualkey::e:
        case Virtualkey::E:
            Interact();
            break;

        case Virtualkey::Space:
            Attack();
            break;

        case Virtualkey::i:
        case Virtualkey::I:
            currentInputMode = CurrentInputMode::Inventory;
            inventoryCursorIndex = 0;
            break;

        default:
            break;
    }
}

void Player::ProcessInventoryModeInput(Virtualkey inputKey)
{
    int minIndex = GetInventoryMinIndexForCurrentPage();
    int maxIndex = GetInventoryMaxIndexForCurrentPage();

    switch (inputKey)
    {
        case Virtualkey::Up:
            inventoryCursorIndex = max(minIndex, inventoryCursorIndex - 1);
            break;

        case Virtualkey::Down:
            {
                inventoryCursorIndex = min(maxIndex, inventoryCursorIndex + 1);
            }
            break;

        case Virtualkey::Left:
            {
                inventoryPageIndex = max(0, inventoryPageIndex - 1);
                inventoryCursorIndex = GetInventoryMinIndexForCurrentPage();
            }
            break;

        case Virtualkey::Right:
            {
                int maxPageIndex = (int)ceil((float)inventory.size() / DISPLAY_INVENTORY_COUNT_PER_PAGE) - 1;
                inventoryPageIndex = min(maxPageIndex, inventoryPageIndex + 1);
                inventoryCursorIndex = GetInventoryMinIndexForCurrentPage();
            }
            break;

        case Virtualkey::Escape:
            {
                currentInputMode = CurrentInputMode::Ingame;
                inventoryCursorIndex = -1;
            }
            break;

        case Virtualkey::Space:
            {
                if (inventory.size() == 0)
                    break;

                InventoryItem& selectedItem = inventory[inventoryCursorIndex];
                ItemType itemType = selectedItem.GetItemType();
                auto itemData = selectedItem.GetItemDataFromTable();

                switch (itemType)
                {
                    case ItemType::None:
                        break;
                    case ItemType::Consumable:
                        {
                            shared_ptr<ConsumableItemData> consumableData = dynamic_pointer_cast<ConsumableItemData>(itemData);
                            assert(consumableData && "Item data is not of type ConsumableItemData");
                            //town portal scroll
                            if(consumableData->key == 2012)
                            {
                                shared_ptr<EventParameter> eventParam 
                                    = make_shared<EventParameter>(EventType::OnUseTownPortalScroll);
                                
                                ObjectManager::GetInstance().BroadcastEvent(eventParam);
                                
                                AddItemQuantity(consumableData->key, consumableData->itemType, -1);

                                Logger::LogInfo("Using townportal scroll");
                            }
                            else
                            {
                                playerStat->AddBuff(consumableData);
                                AddItemQuantity(consumableData->key, consumableData->itemType, -1);

                                Logger::LogInfo(format("Used item: {0} x{1}", selectedItem.GetName(), selectedItem.GetQuantity()));
                            }
                        }
                        break;

                    case ItemType::Gear:
                        {
                            shared_ptr<GearData> gearData = dynamic_pointer_cast<GearData>(itemData);
                            assert(gearData && "Item data is not of type GearData");
                            if (gearData->minLevel > playerLevel)
                            {
                                Logger::LogInfo(format("Not enough level, required level: {}", gearData->minLevel ));
                                return;
                            }

                            AddItemQuantity(gearData->key, gearData->itemType, -1);
                            EquipItem(gearData->key, gearData->itemType);
                        }
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}