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
    initHp = constructionParams->initHp;
    attack = constructionParams->attack;
    defense = constructionParams->defense;
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
        default:
            break;
    }
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
        monster->TakeDamage(attack);
        if (!monster->IsDead())
            continue;

        AddItems(monster->GetDropItems());
        AddExp(monster->GetExp());
    }
}

void Player::AddItems(vector<DropItemData>& dropItems)
{
    for (auto& dropItem : dropItems)
    {
        InventoryItem newItem(dropItem.GetItemName(), dropItem.GetCount());
        inventory.emplace_back(newItem);

        Logger::LogInfo(format("{} {}개 추가됨", 
            newItem.GetName(), newItem.GetQuantity()));
    }    
}

void Player::AddExp(int exp)
{
    this->currentExp += exp;

    Logger::LogInfo(format("{} 경험치 획득", exp));
}
