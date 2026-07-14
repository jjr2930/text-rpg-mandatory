#include "GameTime.h"
#include <chrono>

using namespace std;

SINGLETON_INITIALIZER(GameTime);

/// <summary>
/// 초로 변환된 게임 시간을 반환합니다.
/// </summary>
/// <returns></returns>
double GameTime::GetTime() const
{
    auto now = chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> msec = now - start;
    return msec.count() / 1000.0;
}

void GameTime::Init()
{
    start = chrono::high_resolution_clock::now();
}