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

using namespace std;

Player::Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , playerLevel(1)
    , currentInputMode(CurrentInputMode::Ingame)
{
    inventoryCursorIndex = -1;
    maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);
   
    //add every alchemy ingredients to the inventory
    //auto& allAchemyData = AlchemyTable::GetInstance().GetAllAlchemyData();
    //for (auto& iter : allAchemyData)
    //{
    //    for (auto& ingredient : iter->ingredients)
    //    {
    //        AddItemQuantity(ingredient.itemKey, ItemType::Ingredient, ingredient.quantity);
    //    }
    //}

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

                    case CurrentInputMode::Inetraction:
                        //in this case, the input is handled by the current interactable object
                        break;
                    default:
                        break;
                }
            }
            break;

        case EventType::OnStopInteraction:
            {
                if (currentInputMode == CurrentInputMode::Inetraction)
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
    if (HasItem(fieldItemm.GetTableKey(), &foundIdex))
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

        Logger::LogInfo(format("Item {0} X{1} added to inventory."
            , newItem.GetName(), newItem.GetQuantity()));
    }

    inventoryCursorIndex = min(inventoryCursorIndex, (int)inventory.size() - 1);
}

void Player::SetItemQuantity(int tableKey, ItemType itemType, int quantity)
{
    int foundIndex;
    if (!HasItem(tableKey, &foundIndex))
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

const vector<InventoryItem>& Player::GetInventory() const
{
    return inventory;
}

bool Player::HasEnoughItem(int tableKey, int quantity) const
{
    for (const auto& item : inventory)
    {
        if (item.GetTableKey() == tableKey && item.GetQuantity() >= quantity)
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

        monster->TakeDamage(playerStat->GetStat(StatType::Attack));
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

    currentInputMode = CurrentInputMode::Inetraction;

    ObjectManager::GetInstance().BroadcastEvent(make_shared<InteractionStartEventParameter>(interactableObject));
}

void Player::AddItems(shared_ptr<MonsterItemDropData> dropItem)
{
    if (nullptr == dropItem)
        return;

    int index;
    MinMaxInt minMaxQuantity(dropItem->minQuantity, dropItem->maxQuantity);
    int randomQuantity = minMaxQuantity.GetRandomValue();
        
    if (HasItem(dropItem->key, &index))
    {
        inventory[index].AddQuantity(randomQuantity);
        Logger::LogInfo(format("{} x{} added", dropItem->key, randomQuantity));
    }
    else
    {
        InventoryItem newItem(dropItem->key, ItemType::Ingredient, randomQuantity);
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
       
        float nextMaxHealth = fInitMaxHp * factor;
        float nextAttack = fInitAttack * factor;
        float nextDefense = fInitDefense * factor;

        playerStat->SetStat(StatType::MaxHealth, nextMaxHealth);
        playerStat->SetStat(StatType::Attack, nextAttack);
        playerStat->SetStat(StatType::Defense, nextDefense);        

        maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);
        Logger::LogInfo(format("level up!: {0}, maxHp -> {1}, atk -> {2}, def -> {3}",
            playerLevel, playerStat->GetStat(StatType::MaxHealth), playerStat->GetStat(StatType::Attack), playerStat->GetStat(StatType::Defense)));
    }

}

bool Player::HasItem(int tableKey, int* index) const
{
    int count = static_cast<int>(inventory.size());
    for (int i = 0; i < count; ++i)
    {
        if (inventory[i].GetTableKey() == tableKey)
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
        case Virtualkey::w:
        case Virtualkey::W:
            playerPosition->TryMoveYOnly(-1);
            break;
                    
        case Virtualkey::s:
        case Virtualkey::S:
            playerPosition->TryMoveYOnly(1);
            break;

        case Virtualkey::a:
        case Virtualkey::A:
            playerPosition->TryMoveXOnly(-1);
            break;

        case Virtualkey::d:
        case Virtualkey::D:
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
    switch (inputKey)
    {
        case Virtualkey::w:
        case Virtualkey::W:
            inventoryCursorIndex = max(0, inventoryCursorIndex - 1);
            break;

        case Virtualkey::s:
        case Virtualkey::S: 
            inventoryCursorIndex = min((int)inventory.size() - 1, inventoryCursorIndex + 1);
            break;

        case Virtualkey::i:
        case Virtualkey::I:
            currentInputMode = CurrentInputMode::Ingame;
            inventoryCursorIndex = -1;
            break;

        case Virtualkey::Space:
            {
                if (inventory.size() == 0)
                    break;

                InventoryItem& selectedItem = inventory[inventoryCursorIndex];
                if (!selectedItem.GetIsUsable())
                {
                    Logger::LogInfo(format("Item {0} is not usable.", selectedItem.GetName()));
                    return;
                }

                Logger::LogInfo(format("Used item: {0} x{1}", selectedItem.GetName(), selectedItem.GetQuantity()));
                
                auto itemData = selectedItem.GetItemDataFromTable();

                if (itemData->itemType != ItemType::Consumable)
                {
                    Logger::LogInfo(format("{0} is not a consumable.", selectedItem.GetName()));
                }
                
                shared_ptr<ConsumableItemData> consumableData = dynamic_pointer_cast<ConsumableItemData>(itemData);
                assert(consumableData && "Item data is not of type ConsumableItemData");
                playerStat->AddBuff(consumableData);
                AddItemQuantity(consumableData->key, consumableData->itemType, -1);
            }
            break;
        default:
            break;
    }
}