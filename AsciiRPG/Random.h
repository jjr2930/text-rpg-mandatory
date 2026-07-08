#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include "SingletonMacro.h"

class Random
{
    SINGLETON(Random)

public:
    void Init();

    // 정수 범위 랜덤 [min, max] (양 끝 포함)
    int RandomRange(int min, int max);
    int64_t RandomRange(int64_t min, int64_t max);

    // 실수 범위 랜덤 [min, max) (min 포함, max 미포함)
    float RandomRange(float min, float max);
    double RandomRange(double min, double max);

private:
    std::mt19937 generator;
};

#endif