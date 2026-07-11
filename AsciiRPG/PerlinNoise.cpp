#include "PerlinNoise.h"

using namespace std;

PerlinNoise::PerlinNoise()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> p(256);
    for (int i = 0; i < 256; i++)
    {
        p[i] = i;
    }

    // 섞기
    std::shuffle(p.begin(), p.end(), gen);

    // 테이블 확장 (0-511)
    std::vector<int> permutation(512);
    for (int i = 0; i < 512; i++)
    {
        permutation[i] = p[i & 255];
    }

    this->permutation = permutation;
}

float PerlinNoise::Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float PerlinNoise::Fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// 그래디언트 계산
float PerlinNoise::Gradient(int hash, float x, float y)
{
    int h = hash & 7;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

float PerlinNoise::GetNoise(float x, float y)
{
    // 정수 부분
    int xi = static_cast<int>(std::floor(x)) & 255;
    int yi = static_cast<int>(std::floor(y)) & 255;

    // 소수 부분
    float xf = x - std::floor(x);
    float yf = y - std::floor(y);

    // Fade 곡선 적용
    float u = Fade(xf);
    float v = Fade(yf);

    // 해시 값 계산
    int aa = permutation[permutation[xi] + yi];
    int ab = permutation[permutation[xi] + yi + 1];
    int ba = permutation[permutation[xi + 1] + yi];
    int bb = permutation[permutation[xi + 1] + yi + 1];

    // 그래디언트 보간
    float x1 = Lerp(Gradient(aa, xf, yf), Gradient(ba, xf - 1, yf), u);
    float x2 = Lerp(Gradient(ab, xf, yf - 1), Gradient(bb, xf - 1, yf - 1), u);

    return Lerp(x1, x2, v);
}