#include <cassert>

#include "DragonBullet.h"
#include "ObjectManager.h"
#include "Position.h"
#include "Entity.h"
#include "Stat.h"
#include "GameTime.h"
#include "Const.h"
#include "Player.h"
#include "MathUtility.h"
#include "Logger.h"
#include "Wall.h"

DragonBullet::~DragonBullet()
{
    Logger::LogInfo("Bullet destroyed");
}

DragonBullet::DragonBullet(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    auto constructionParams = static_cast<ConstructionParameter*>(params.get());

    Vector2 spawnPoint = Vector2(static_cast<float>(constructionParams->spawnPosition.x)
                                , static_cast<float>(constructionParams->spawnPosition.y));

    Vector2 targetPoint = Vector2(static_cast<float>(constructionParams->targetPosition.x)
                                , static_cast<float>(constructionParams->targetPosition.y));

    this->movingSpeed = constructionParams->movingSpeed;
    this->virtualPosition = spawnPoint;
    this->virtualDirection = targetPoint - spawnPoint;
    this->virtualDirection.Normalize(); 
    this->damage = constructionParams->damage;

    if (auto ptr = entity.lock())
    {
        bulletPosition = ptr->GetComponent<Position>();
    }

    assert(nullptr != bulletPosition && "DragonBullet position is null");

    auto[player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
    this->playerPosition = playerPosition;
    this->player = player;
}

void DragonBullet::Start()
{
    bulletPosition->SetPosition(static_cast<int>(virtualPosition.x)
                                , static_cast<int>(virtualPosition.y));
}

void DragonBullet::Update()
{
    double deltaTime = GameTime::GetDeltaTime();
    Vector2 virtualVelocity = virtualDirection * movingSpeed * static_cast<float>(deltaTime);
    virtualPosition += virtualVelocity;

    //conver to real display coordinates system
    int screenX = static_cast<int>(virtualPosition.x);
    int screenY = static_cast<int>(virtualPosition.y);
    Vector2Int screenPosition = Vector2Int(screenX, screenY);

    bulletPosition->SetPosition(screenX, screenY);
    //checking map's size
    if (screenX < 0 || screenX >= Const::Map::DEFAULT_WIDTH) 
    {
        DestroyEntity();
        return;
    }

    if (screenY < 0 || screenY >= Const::Map::DEFAULT_HEIGHT)
    {
        DestroyEntity();
        return;
    }

    auto walls = ObjectManager::GetInstance().GetComponentTupleVector<Wall, Position>();
    
    for (auto& [wall, wallPosition] : walls)
    {
        if (MathUtility::IsOverlap(screenPosition, wallPosition->GetPosition(), 0))
        {
            DestroyEntity();
            return;
        }
    }

    if(MathUtility::IsOverlap(screenPosition, playerPosition->GetPosition(), 0))
    {
        player->TakeDamage(damage);
        DestroyEntity();
        return;
    }
}

void DragonBullet::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnMapClearRequested:
            if (auto entityPtr = entity.lock())
            {
                DestroyEntity();
            }
            break;

        default:
            break;
    }
}
