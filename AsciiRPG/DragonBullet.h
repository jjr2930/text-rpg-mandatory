#ifndef DRAGON_BULLET_H
#define DRAGON_BULLET_H

#include <memory>

#include "Component.h"
#include "Vector2.h"
#include "Vector2Int.h"
#include "IConstructionParameter.h"

class Position;
class Player;

class DragonBullet : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, Vector2Int spawnPosition, Vector2Int targetPosition, float movingSpeed, int damage)
            : Component::ConstructionParamterBase(entity)
            , spawnPosition(spawnPosition)
            , targetPosition(targetPosition)
            , movingSpeed(movingSpeed)
            , damage(damage)
        {
        }

        Vector2Int spawnPosition;
        Vector2Int targetPosition;
        float movingSpeed;
        int damage;
    };
public:
    using Component::Component;
    virtual ~DragonBullet();

    DragonBullet(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    void Start() override;
    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;
public:
    shared_ptr<Position> bulletPosition;
    shared_ptr<Position> playerPosition;
    shared_ptr<Player> player;

    Vector2 virtualDirection;
    Vector2 virtualPosition;
    float movingSpeed;
    int damage;
};

#endif // !DRAGON_BULLET_H