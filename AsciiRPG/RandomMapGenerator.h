#ifndef RANDOM_MAP_GENERATOR_H
#define RANDOM_MAP_GENERATOR_H

#include "Vector2Int.h"
#include "Vector2.h"

#include <memory>
#include <vector>

using namespace std;

class Player;
class Entity;

class RandomMapGenerator
{
public:
    static constexpr char WALL = '#';
    static constexpr char START = 'S';
    static constexpr char EXIT = 'X';
    static constexpr char ITEM = '*';
    static constexpr char MONSTER = 'M';
    static constexpr char EMPTY = ' ';
    static constexpr char PLAYER = 'P';
    const Vector2 NOISE_THRESHOLD_RANGE = Vector2(0.47f, 0.55f); // Perlin Noise 임계값
    const float NOISE_MAX_THRESHOLD = 0.5f; // Perlin Noise 임계값
    const int MAX_ATTEMPTS = 10000; // 최대 재시도 횟수
    const Vector2Int ITEM_COUNT_RANGE = Vector2Int(3, 10); // 아이템 개수 범위
    const Vector2Int MONSTER_COUNT_RANGE = Vector2Int(3, 7); // 몬스터 개수 범위


public:
    void GenerateRandomMap(int width, int height, shared_ptr<Entity> playerEntity = nullptr);

private:
    bool CanReachAllTargets(char**& map, int width, int height, int startX, int startY,
        int exitX, int exitY,
        const std::vector<std::pair<int, int>>& itemPositions,
        const std::vector<std::pair<int, int>>& monsterPositions);
};

#endif // !RANDOM_MAP_GENERATOR_H