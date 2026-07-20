#include "DragonIdleState.h"
#include "GameTime.h"
#include "Logger.h"

#include <format>

void DragonIdleState::Start()
{
    endIdleTime = GameTime::GetInstance().GetTime() + idleDurationRange.GetRandomValue();

    Logger::LogInfo(std::format("Dragon entered idle state. Will end at {}", endIdleTime));
}

double DragonIdleState::GetEndIdleTime() const
{
    return endIdleTime;
}
