#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "Monster.h"
#include "MathUtility.h"
#include "Logger.h"
#include "FieldItem.h"
#include "LevelExpTable.h"

#include <format>


using namespace std;

Player::Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , currentExp(0)
    , playerLevel(1)
    , currentInputMode(CurrentInputMode::Ingame)
{
    auto constructionParams = std::static_pointer_cast<PlayerConstructionParameter>(params);
    maxHp = constructionParams->initHp;
    attack = constructionParams->attack;
    defense = constructionParams->defense;
    currentHp = maxHp;
    inventoryCursorIndex = -1;
    maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);
    if (auto ptr = entity.lock())
        playerPosition = ptr->GetComponent<Position>();
}

void Player::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::KeyPressed:
            {
                InputEventParameter* inputMessage = static_cast<InputEventParameter*>(message.get());
                char inputChar = inputMessage->inputChar;
                switch (currentInputMode)
                {
                    case CurrentInputMode::Ingame:
                        ProcessIngameModeInput(inputChar);
                        break;
                    case CurrentInputMode::Inventory:
                        ProcessInventoryModeInput(inputChar);
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

void Player::TakeDamage(int damage)
{
    int realDamage = damage - defense;
    if (realDamage < 1)
        realDamage = 1;
    
    currentHp -= realDamage;
    if (currentHp <= 0)
    {
        currentHp = 0;
        Logger::LogInfo("Player is dead!");
    }
}

void Player::AddItem(const FieldItem& fieldItemm)
{
    int foundIdex;
    if (HasItem(fieldItemm.GetItemName(), &foundIdex))
    {
        Logger::LogInfo(format("Player already has item: {0}", fieldItemm.GetItemName()));
        inventory[foundIdex].AddQuantity(fieldItemm.GetQuantity());
    }
    else
    {
        inventory.emplace_back(fieldItemm.GetItemName(), fieldItemm.GetQuantity());
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

int Player::GetHp() const
{
    return currentHp;
}

int Player::GetMaxHp() const
{
    return maxHp;
}

int Player::GetAttack() const
{
    return attack;
}

int Player::GetDefense() const
{
    return defense;
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
        monster->TakeDamage(attack);
        if (!monster->IsDead())
            continue;

        AddItems(dropItem);
        AddExp(exp);
    }
}

void Player::AddItems(vector<DropItemData>& dropItems)
{
    for (auto& dropItem : dropItems)
    {
        int index;
        if (HasItem(dropItem.GetItemName(), &index))
        {
            inventory[index].AddQuantity(dropItem.GetCount());
            Logger::LogInfo(format("{} x{} added", dropItem.GetItemName(), dropItem.GetCount()));
            continue;
        }

        InventoryItem newItem(dropItem.GetItemName(), dropItem.GetCount());
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
        

        float fInitMaxHp = static_cast<float>(Player::INIT_HP);
        float fInitAttack = static_cast<float>(Player::INIT_ATTACK);
        float fInitDefense = static_cast<float>(Player::INIT_DEFENSE);

        float r = 1.1f; 
        //복리 계산하기 (1+0.1)10−1
        float factor = pow(r, static_cast<float>(playerLevel - 1));
       
        maxHp = static_cast<int>(fInitMaxHp * factor);
        attack = static_cast<int>(fInitAttack * factor);
        defense = static_cast<int>(fInitDefense * factor);        

        maxExp = LevelExpTable::GetInstance().GetExpForLevel(playerLevel + 1);
        Logger::LogInfo(format("level up!: {0}, maxHp -> {1}, atk -> {2}, def -> {3}",
            playerLevel, maxHp, attack, defense));
    }

}

bool Player::HasItem(const string& itemName, int* index) const
{
    int count = inventory.size();
    for (int i = 0; i < count; ++i)
    {
        if (inventory[i].GetName() == itemName)
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

void Player::ProcessIngameModeInput(char inputChar)
{
    switch (inputChar)
    {
        case 'w':
            playerPosition->TryMoveYOnly(-1);
            break;
                    
        case 's':
            playerPosition->TryMoveYOnly(1);
            break;

        case 'a':
            playerPosition->TryMoveXOnly(-1);
            break;

        case 'd':
            playerPosition->TryMoveXOnly(1);
            break;

        case ' ':
            Attack();
            break;

        case 'i':
            currentInputMode = CurrentInputMode::Inventory;
            inventoryCursorIndex = 0;
            break;

        default:
            break;
    }
}

void Player::ProcessInventoryModeInput(char inputChar)
{
    switch (inputChar)
    {
        case 'w':
            inventoryCursorIndex = max(0, inventoryCursorIndex - 1);
            break;

        case 's':
            inventoryCursorIndex = min((int)inventory.size() - 1, inventoryCursorIndex + 1);
            break;

        case 'i':
            currentInputMode = CurrentInputMode::Ingame;
            inventoryCursorIndex = -1;
            break;

        case ' ':
            {
                if (inventory.size() == 0)
                    break;

                InventoryItem& selectedItem = inventory[inventoryCursorIndex];
                Logger::LogInfo(format("Used item: {0} x{1}", selectedItem.GetName(), selectedItem.GetQuantity()));
                if (selectedItem.GetName() == "Potion")
                {
                    currentHp = min(maxHp, currentHp + 20);
                    Logger::LogInfo(format("Restored 20 HP. Current HP: {0}/{1}", currentHp, maxHp));
                    selectedItem.AddQuantity(-1);

                    if (selectedItem.GetQuantity() > 0)
                        break;
                    
                    inventory.erase(inventory.begin() + inventoryCursorIndex);
                    if (inventoryCursorIndex >= inventory.size())
                    {
                        inventoryCursorIndex = max(0, (int)inventory.size() - 1);
                    }                    
                }
            }
            break;
        default:
            break;
    }
}
