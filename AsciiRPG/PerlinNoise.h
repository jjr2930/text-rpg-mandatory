#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H
#include <random>
#include <vector>

using namespace std;

class PerlinNoise
{
public :
    PerlinNoise();

    float GetNoise(float x, float y);

private:
    // 선형 보간
    float Lerp(float a, float b, float t);

    // 부드러운 보간 (smoothstep)
    float Fade(float t); 

    // 그래디언트 계산
    float Gradient(int hash, float x, float y);

    // Perlin Noise 함수
private:
    vector<int> permutation;
};

#endif // !PERLIN_NOISE_H
