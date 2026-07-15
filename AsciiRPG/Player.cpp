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
#include "ItemData.h"
#include "ItemTable.h"
#include "InteractableObject.h"

#include <format>
#include <cassert>

using namespace std;

Player::Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , currentExp(0)
    , playerLevel(1)
    , currentInputMode(CurrentInputMode::Ingame)
{
    inventoryCursorIndex = -1;
    maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);

    if (auto ptr = entity.lock())
    {
        playerPosition = ptr->GetComponent<Position>();
        playerStat = ptr->GetComponent<Stat>();
    }
}

void Player::HandleEvent(shared_ptr<EventParameter> message)
{
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
                currentInputMode = CurrentInputMode::Ingame;
                currentInteractableObject->OnDisable();
                currentInteractableObject = nullptr;
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
        inventory.emplace_back(fieldItemm.GetTableKey(), fieldItemm.GetQuantity());
    }
}

int Player::GetLevel() const
{
    return playerLevel;
}

int Player::GetExp() const
{
    return currentExp;
}

int Player::GetCurrentHelath() const
{
    return static_cast<int>(playerStat->GetStat(StatType::CurrentHealth));
}

int Player::GetMaxHp() const
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
    return inventory.size();
}

int Player::GetInventoryCursorIndex() const
{
    return inventoryCursorIndex;
}

const vector<InventoryItem>& Player::GetInventory() const
{
    return inventory;
}

void Player::Attack()
{
    auto components = ObjectManager::GetInstance().GetComponentsWithTypes<Monster, Position>();
    Vector2Int position = playerPosition->GetPosition();
    for (auto& [monster, monsterPosition] : components)
    {
        Vector2Int monsterPos = monsterPosition->GetPosition();
        if (!MathUtility::IsOverlap(position, monsterPos, 1))
            continue;
        
        Logger::LogInfo("ATTACK!!");

        vector<DropItemData> dropItem = monster->GetDropItems();
        int exp = monster->GetExp();
        monster->TakeDamage(playerStat->GetStat(StatType::Attack));
        if (!monster->IsDead())
            continue;

        AddItems(dropItem);
        AddExp(exp);
    }
}

void Player::Interact()
{
    auto components = ObjectManager::GetInstance().GetComponentsWithTypes<InteractableObject, Position>();

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

void Player::AddItems(vector<DropItemData>& dropItems)
{
    for (auto& dropItem : dropItems)
    {
        int index;
        if (HasItem(dropItem.GetTableKey(), &index))
        {
            inventory[index].AddQuantity(dropItem.GetCount());
            Logger::LogInfo(format("{} x{} added", dropItem.GetTableKey(), dropItem.GetCount()));
            continue;
        }

        InventoryItem newItem(dropItem.GetTableKey(), dropItem.GetCount());
        inventory.emplace_back(newItem);

        Logger::LogInfo(format("{} x{} added", 
            newItem.GetName(), newItem.GetQuantity()));
    }    
}

void Player::AddExp(int exp)
{
    this->currentExp += exp;

    Logger::LogInfo(format("{} exp added", exp));
    
    if (currentExp >= maxExp)
    {
        playerLevel++;
        currentExp -= maxExp;
        
        float fInitMaxHp = static_cast<float>(Const::Stat::Player::INIT_HP);
        float fInitAttack = static_cast<float>(Const::Stat::Player::INIT_ATTACK);
        float fInitDefense = static_cast<float>(Const::Stat::Player::INIT_DEFENSE);

        float r = 1.1f; 
        //복리 계산하기 (1+0.1)10−1
        float factor = pow(r, static_cast<float>(playerLevel - 1));
       
        int nextMaxHealth = static_cast<int>(fInitMaxHp * factor);
        int nextAttack = static_cast<int>(fInitAttack * factor);
        int nextDefense = static_cast<int>(fInitDefense * factor);

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

void Player::AddItemQuantity(int tableKey, int quantity)
{
    for (auto iter = inventory.begin(); iter != inventory.end(); ++iter)
    {
        if (iter->GetTableKey() == tableKey)
        {
            iter->AddQuantity(quantity);
            if (iter->GetQuantity() <= 0)
            {
                Logger::LogInfo(format("Item {0} removed from inventory.", iter->GetName()));
                inventory.erase(iter);
            }
            return;
        }
    }

    inventoryCursorIndex = min(inventoryCursorIndex, (int)inventory.size() - 1);
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

                playerStat->AddBuff(*itemData);
                
                AddItemQuantity(selectedItem.GetTableKey(), -1);
            }
            break;
        default:
            break;
    }
}