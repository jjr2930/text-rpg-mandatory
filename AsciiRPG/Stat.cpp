#include "Stat.h"
#include "Logger.h"
#include "GameTime.h"
#include "ItemData.h"
#include <format>

#include <cassert>
#include <algorithm>

Stat::Stat(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    :Component(id, name, params)
{
    auto constructionParams = static_cast<ConstructionParameter*>(params.get());

    stats = constructionParams->initialStats;
}

void Stat::AddBuff(StatType statType, OperatorType operatorType, float value, bool isInstant, double duration, double interval)
{
    Buff newBuff(statType, operatorType, value, isInstant, duration, interval);
    if (isInstant)
    {
        assert(stats.contains(statType) && "StatType does not exist in stats. Cannot apply instant buff."); 

        ProcessBuff(newBuff);
    }
    else
    {
        buffs.emplace_back(newBuff);
    }
}

void Stat::AddBuff(const ItemData& itemData)
{
    AddBuff(itemData.statType, itemData.operatorType, itemData.amount, itemData.isInstant, itemData.duration, itemData.interval);
}

void Stat::AddStat(StatType statType, float value)
{
    stats[statType] += value;
}

void Stat::SetStat(StatType statType, float value)
{
    stats[statType] = value;
}

void Stat::Update()
{
    double nowTime = GameTime::GetInstance().GetTime();
    for (auto iter = buffs.begin(); iter != buffs.end();)
    {
        if (nowTime - iter->lastAppliedTime >= iter->interval)
        {
            assert(stats.contains(iter->statType) && "StatType does not exist in stats. Cannot apply instant buff."); 
            
            ProcessBuff(*iter);

            iter->lastAppliedTime = nowTime;
        }

        if (nowTime - iter->startTime >= iter->duration)
        {
            iter = buffs.erase(iter);
            continue;
        }

        ++iter;
    }
}

float Stat::GetStat(StatType statType) 
{
    assert(stats.contains(statType) && "StatType does not exist in stats. Cannot apply instant buff."); 

    return stats[statType];
}

void Stat::ProcessBuff(Buff& buff)
{
    Logger::LogInfo(std::format("Applied buff: {},{},{}", 
         EnumUtility::ToString(buff.statType), EnumUtility::ToString(buff.operatorType), buff.value));

    switch (buff.operatorType)
    {
        case OperatorType::Add:
            stats[buff.statType] += buff.value;
            break;

        case OperatorType::Subtract:
            stats[buff.statType] -= buff.value;
            break;

        case OperatorType::Multiply:
            stats[buff.statType] *= buff.value;
            break;

        case OperatorType::Divide:
            stats[buff.statType] /= buff.value;
            break;

        default:
            break;
    }

    //clamp health stat... very wired
    stats[StatType::CurrentHealth] = std::clamp(stats[StatType::CurrentHealth], 0.0f, stats[StatType::MaxHealth]);

}

Stat::Buff::Buff(StatType statType, OperatorType operatorType, float value, bool isInstant , double duration, double interval )
    : statType(statType)
    , operatorType(operatorType)
    , value(value)
    , isInstant(isInstant)
    , duration(duration)
    , interval(interval)
    , lastAppliedTime(0.0)
    , startTime(0.0)
{
}