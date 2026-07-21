#include "DragonIdleState.h"
#include "GameTime.h"
#include "Logger.h"

#include <format>

void DragonIdleState::Start()
{
    double now = GameTime::GetInstance().GetTime();
    double randomInterval = idleDurationRange.GetRandomValue();
    endIdleTime = now + randomInterval;

    Logger::LogInfo(std::format("Dragon entered idle state. Will end at {}", endIdleTime));
}

double DragonIdleState::GetEndIdleTime() const
{
    return endIdleTime;
}
