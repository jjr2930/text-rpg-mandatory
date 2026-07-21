#include "DragonRangeAttack.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Position.h"
#include "Dragon.h"
#include "GameTime.h"
#include "DragonBullet.h"
#include "CreationUtil.h"
#include "Stat.h"

DragonRangeAttack::DragonRangeAttack(MinMaxDouble attackDelayRange, MinMaxInt attackCountRange)
    : attackDelayRange(attackDelayRange)
    , attackCountRange(attackCountRange)
{}

void DragonRangeAttack::Start()
{
    auto [player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
    auto [dragon, dragonPosition, dragonStat] = ObjectManager::GetInstance().GetComponentTuple<Dragon, Position, Stat>();

    this->playerPosition = playerPosition;
    this->dragonPosition = dragonPosition;
    this->dragonStat = dragonStat;

    totalAttackCount = attackCountRange.GetRandomValue();
    attackDelay = attackDelayRange.GetRandomValue();
    currentAttackCount = 0;
    lastAttackTime = 0.0;
}

void DragonRangeAttack::Update()
{
    if(GameTime::GetTime() - lastAttackTime >= attackDelay)
    {
        // Perform attack logic here
        // TODO: bullet damage should be based on dragon's attack stat or from monster table data
        auto bullet = CreationUtil::CreateDragonBullet(dragonPosition->GetPosition(), playerPosition->GetPosition(), 10);

        currentAttackCount++;
        lastAttackTime = GameTime::GetTime();
    }
}

bool DragonRangeAttack::AmIDead() const
{
    return dragonStat->GetStat(StatType::CurrentHealth) <= 0;
}

bool DragonRangeAttack::IsShootingFinished() const
{
    return currentAttackCount >= totalAttackCount;
}
