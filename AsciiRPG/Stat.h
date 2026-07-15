#ifndef STAT_H
#define STAT_H

#include "Component.h"
#include "Enums.h"

#include <unordered_map>

struct ItemData;

class Stat : public Component
{
public :
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, const unordered_map<StatType, float>& initialStats)
            : Component::ConstructionParamterBase(entity)
            , initialStats(initialStats)
        {}

        unordered_map<StatType, float> initialStats;
    };

    class Buff {
    public:
        Buff(StatType statType, OperatorType operatorType, float value, bool isInstant , double duration, double interval );
        StatType statType;
        OperatorType operatorType;
        bool isInstant;
        double duration;
        float value;
        double lastAppliedTime; // 마지막으로 적용된 시간
        double startTime;
        double interval; // 버프 적용 간격 (초)
    };

    using Component::Component;
    Stat(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);

    void AddBuff(StatType statType, OperatorType operatorType, float value, bool isInstant , double duration, double interval);
    void AddBuff(const ItemData& itemData);
    void AddStat(StatType statType, float value);

    //setter
    void SetStat(StatType statType, float value);
    
    //getter
    float GetStat(StatType statType);
    
    void Update() override;

protected:
    void ProcessBuff(Buff& buff);
protected:
    unordered_map<StatType, float> stats;
    vector<Buff> buffs;
};

#endif // !STAT_H