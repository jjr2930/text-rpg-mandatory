#include "Player.h"
#include "Position.h"
#include "Entity.h"
#include "Position.h"
#include "Monster.h"
#include "MathUtility.h"


Player::Player(int64_t id, const std::string& name)
    : Component(id, name, nullptr)
    , initHp(0)
    , attack(0)
    , defense(0)
{
}

Player::Player(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
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
        if (MathUtility::IsOverlap(position, monsterPos, 1))
        {
            monster->TakeDamage(attack);
        }
    }
}


