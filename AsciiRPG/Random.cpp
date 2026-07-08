#include "Random.h"
#include <chrono>

SINGLETON_INITIALIZER(Random)

void Random::Init()
{
    // 현재 시간을 시드로 사용
    auto seed = static_cast<unsigned int>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    generator.seed(seed);
}

int Random::RandomRange(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

int64_t Random::RandomRange(int64_t min, int64_t max)
{
    std::uniform_int_distribution<int64_t> distribution(min, max);
    return distribution(generator);
}

float Random::RandomRange(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

double Random::RandomRange(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}
