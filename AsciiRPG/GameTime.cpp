#include "GameTime.h"
#include <chrono>

using namespace std;

SINGLETON_INITIALIZER(GameTime);


double GameTime::GetTime()
{
    return GetInstance().OnGetTime();
}

double GameTime::GetDeltaTime()
{
    return GetInstance().deltaTime;
}

void GameTime::CalculateDeltaTime()
{
    auto now = chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationInSec = now - GetInstance().lastDeltaSpampedTime;
    GetInstance().deltaTime = durationInSec.count();
    GetInstance().lastDeltaSpampedTime = now;
}

double GameTime::OnGetTime() const
{
    auto now = chrono::high_resolution_clock::now();

    std::chrono::duration<double> sec = now - start;
    return sec.count();
}

void GameTime::Init()
{
    start = chrono::high_resolution_clock::now();
}