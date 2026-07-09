#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "Monster.h"
#include "MathUtility.h"
#include "Logger.h"
#include <format>

using namespace std;

Player::Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , currentExp(0)
    , playerLevel(1)
{
    playerPosition = entity->GetComponent<Position>();

    auto constructionParams = std::static_pointer_cast<PlayerConstructionParameter>(params);
    maxHp = constructionParams->initHp;
    attack = constructionParams->attack;
    defense = constructionParams->defense;
    currentHp = maxHp;
}

void Player::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::KeyPressed:
            {
                InputEventParameter* inputMessage = static_cast<InputEventParameter*>(message.get());
                char inputChar = inputMessage->inputChar;
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
