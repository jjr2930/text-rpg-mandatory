#include <cassert>

#include "DragonAttackState.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Position.h"
#include "MathUtility.h"
#include "Dragon.h"
#include "Stat.h"
#include "Entity.h"
#include "GameTime.h"

DragonAttackState::DragonAttackState(double attackDelay)
    : attackDelay(attackDelay)
{}

void DragonAttackState::Start()
{
    auto [player, playerPosition, playerStat] = ObjectManager::GetInstance().GetComponentTuple<Player, Position, Stat>();
    auto [dragon, dragonPosition, dragonStat] = ObjectManager::GetInstance().GetComponentTuple<Dragon, Position, Stat>();
    
    this->player = player;
    this->playerPosition = playerPosition;
    this->playerStat = playerStat;

    this->dragon = dragon;
    this->dragonPosition = dragonPosition;
    this->dragonStat = dragonStat;
}

void DragonAttackState::Update()
{
    double currentTime = GameTime::GetInstance().GetTime();
    if (currentTime - lastAttackTime >= attackDelay) // Attack interval = 1 second
    {
        player->TakeDamage(static_cast<int>(dragonStat->GetStat(StatType::Attack)));

        // Perform attack logic here
        lastAttackTime = currentTime;
    }
}

bool DragonAttackState::OutOfRangeWithPlayer() const
{
    assert(nullptr != playerPosition && "Player position is null");
    assert(nullptr != dragonPosition && "Dragon position is null");

    //range = 1;
    // Example range check (replace with actual logic)
    if(MathUtility::IsOverlap(playerPosition->GetPosition(), dragonPosition->GetPosition(), 1))
    {
        return false;
    }

    return true;
}   
