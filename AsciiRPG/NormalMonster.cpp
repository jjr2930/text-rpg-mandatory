#include "NormalMonster.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Vector2Int.h" 
#include "Position.h"
#include "Logger.h"
#include "MathUtility.h"
#include "Stat.h"
#include "GameTime.h"

void NormalMonster::Update()
{
    Monster::Update();

    auto [player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
    if (!player || !playerPosition)
    {
        Logger::LogError("There should be exactly one player in the game.");
        return;
    }

    Vector2Int myPosition = monsterPosition->GetPosition();

    if (!MathUtility::IsOverlap(myPosition, playerPosition->GetPosition(), 1))
    {
        fistOverlap = false;
        return;
    }

    float attackDelay = monsterStat->GetStat(StatType::AttackDelay);
    float attack = monsterStat->GetStat(StatType::Attack);

    if(!fistOverlap)
    {
        fistOverlap = true;
        nextAttackTime = GameTime::GetNow();
        nextAttackTime += (double)attackDelay;
    }

    else if(GameTime::GetNow() >= nextAttackTime)
    {
        string name = "";
        if (auto ptr = entity.lock())
        {
            name = ptr->GetName();
        }

        Logger::LogError(format("{}(hp:{}) attacks({}) you", name, (int)monsterStat->GetStat(StatType::CurrentHealth), attack));
        player->TakeDamage(attack);
        nextAttackTime = GameTime::GetNow();
        nextAttackTime += (double)attackDelay;
    }    
}
