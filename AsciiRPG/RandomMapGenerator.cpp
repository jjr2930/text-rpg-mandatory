#include "RandomMapGenerator.h"
#include "PerlinNoise.h"
#include "Random.h"
#include "Logger.h"
#include "CreationUtil.h"
#include "Player.h"
#include "Entity.h"
#include "Position.h"
#include "Vector2Int.h"
#include "Const.h"
#include "Map.h"
#include "MonsterTable.h"
#include "MinMax.h"

#include <algorithm>
#include <queue>

void RandomMapGenerator::GenerateRandomMap(int width, int height, int floor, shared_ptr<Map> outputMap)
{
    PerlinNoise perlinNoise;
    bool loop = true;
    while (loop)
    {
        // 사용자로부터 임계값 입력받기
        float threshold = Random::GetInstance()
            .RandomRange(NOISE_THRESHOLD_RANGE.x, NOISE_THRESHOLD_RANGE.y);
            
        bool validMap = false;
        int startX, startY, exitX, exitY;
        int attemptCount = 0;
        int totalItemCount = 0; // 생성된 아이템 수
        int totalMonsterCount = 0; // 생성된 몬스터 수
        const int MAX_ATTEMPTS = 100; // 최대 재시도 횟수

        // 유효한 맵이 생성될 때까지 반복
        while (!validMap && attemptCount < MAX_ATTEMPTS)
        {
            attemptCount++;
            
            outputMap->Clear(); // 맵 초기화

            // 테두리 벽 생성
            for (int x = 0; x < width; x++)
            {
                outputMap->SetCellData(x, 0, DungeonTagTypes::Wall);
                outputMap->SetCellData(x, height - 1, DungeonTagTypes::Wall);
            }
            for (int y = 0; y < height; y++)
            {
                outputMap->SetCellData(0, y, DungeonTagTypes::Wall);
                outputMap->SetCellData(width - 1, y, DungeonTagTypes::Wall);
            }

            float scale = 0.15f; // Noise 스케일 (작을수록 부드러운 패턴)

            for (int y = 1; y < height - 1; y++)
            {
                for (int x = 1; x < width - 1; x++)
                {
                    float noiseValue = perlinNoise.GetNoise(x * scale, y * scale);
                    // Perlin Noise 값을 0~1 범위로 정규화
                    noiseValue = (noiseValue + 1.0f) / 2.0f;

                    // 임계값을 넘으면 벽 생성
                    if (noiseValue > threshold)
                    {
                        outputMap->SetCellData(x, y, DungeonTagTypes::Wall);
                    }
                }
            }

            // 시작 지점(S) 배치
            do
            {
                startX = Random::GetInstance().RandomRange(1, width - 2);
                startY = Random::GetInstance().RandomRange(1, height - 2);
            } while (outputMap->GetCellData(startX, startY) != DungeonTagTypes::None);
            outputMap->SetCellData(startX, startY, DungeonTagTypes::Entrance);

            // 상하 좌우에 유저를 배치할 위치를 찾는다.

            int simpleDistanceWithEntrance = 0;
            // 출구(X) 배치
            do
            {
                exitX = Random::GetInstance().RandomRange(1, width - 2);
                exitY = Random::GetInstance().RandomRange(1, height - 2);

                simpleDistanceWithEntrance = std::abs(exitX - startX) + std::abs(exitY - startY);
            } while (outputMap->GetCellData(exitX, exitY) != DungeonTagTypes::None && simpleDistanceWithEntrance < 40);

            outputMap->SetCellData(exitX, exitY, DungeonTagTypes::Exit);

            // 아이템(*) 배치 (3-10개 랜덤)
            int itemCount = Random::GetInstance().RandomRange(ITEM_COUNT_RANGE.x, ITEM_COUNT_RANGE.y);

            std::vector<std::pair<int, int>> itemPositions;
            for (int i = 0; i < itemCount; i++)
            {
                int itemX, itemY;
                do
                {
                    itemX = Random::GetInstance().RandomRange(1, width - 2);
                    itemY = Random::GetInstance().RandomRange(1, height - 2);
                } while (outputMap->GetCellData(itemX, itemY) != DungeonTagTypes::None); // 빈 공간에만 배치

                outputMap->SetCellData(itemX, itemY, DungeonTagTypes::FieldDropItem);
                itemPositions.push_back({ itemX, itemY });
            }

            // 몬스터(M) 배치 (3-7개 랜덤)
            int monsterCount = Random::GetInstance().RandomRange(MONSTER_COUNT_RANGE.x, MONSTER_COUNT_RANGE.y);
            std::vector<std::pair<int, int>> monsterPositions;

            auto possibleMonsters = MonsterTable::GetInstance().GetMonstersByFloor(floor);
            MinMaxInt monsterIndexRange(0, static_cast<int>(possibleMonsters.size()) - 1);

            for (int i = 0; i < monsterCount; i++)
            {
                int monsterX, monsterY;
                do
                {
                    monsterX = Random::GetInstance().RandomRange(1, width - 2);
                    monsterY = Random::GetInstance().RandomRange(1, height - 2);
                } while (outputMap->GetCellData(monsterX, monsterY) != DungeonTagTypes::None); // 빈 공간에만 배치

                shared_ptr<MonsterData> randomMonster = possibleMonsters[monsterIndexRange.GetRandomValue()];

                DungeonTagTypes tag = EnumUtility::ToDungeonTagTypes(randomMonster->displayChar);
                outputMap->SetCellData(monsterX, monsterY, tag);
                monsterPositions.push_back({ monsterX, monsterY });
            }

            // 시작 지점에서 출구, 모든 아이템, 모든 몬스터에 접근 가능한지 확인
            if (CanReachAllTargets(outputMap, width, height, startX, startY, exitX, exitY, itemPositions, monsterPositions))
            {
                validMap = true;
                totalItemCount = itemCount; // 성공한 맵의 아이템 개수 저장
                totalMonsterCount = monsterCount; // 성공한 맵의 몬스터 개수 저장
            }
        }

        // 최대 시도 횟수 초과 시 처리
        if (!validMap)
        {
            //Logger::LogInfo("Map Generation Failed");
            continue; // 다시 임계값 입력으로 돌아감
        }

        //Logger::LogInfo("Map Generation Completed (Items: " + std::to_string(totalItemCount) + ", Monsters: " + std::to_string(totalMonsterCount) + ", Attempts: " + std::to_string(attemptCount) + ")\n\n");

        break;
    }

    //// 맵 데이터를 Map 객체에 적용
    //for (int y = 0; y < height; y++)
    //{
    //    for (int x = 0; x < width; x++)
    //    {
    //        char cellChar = map[y][x];
    //        switch (cellChar)
    //        {
    //            case Const::Map::WALL:
    //                CreationUtil::CreateWall(Vector2Int(x, y));
    //                break;

    //            case Const::Map::START:
    //                CreationUtil::CreateEntrance(Vector2Int(x, y));
    //                break;

    //            case Const::Map::EXIT:
    //                CreationUtil::CreateExit(Vector2Int(x, y));
    //                break;

    //            case Const::Map::ITEM:
    //                CreationUtil::CreateFieldItem(Vector2Int(x, y), "Potion", 1);
    //                break;

    //            case Const::Map::MONSTER:
    //                CreationUtil::CreateMonster(Vector2Int(x, y));
    //                break;

    //            default:
    //                break;
    //        }
    //    }
    //}
}

bool RandomMapGenerator::CanReachAllTargets(shared_ptr<Map> outputMap, int width, int height, int startX, int startY, int exitX, int exitY, const std::vector<std::pair<int, int>>& itemPositions, const std::vector<std::pair<int, int>>& monsterPositions)
{
    // 동적 2D 배열로 visited 생성
    bool** visited = new bool*[height];
    for (int i = 0; i < height; i++)
    {
        visited[i] = new bool[width];
        for (int j = 0; j < width; j++)
        {
            visited[i][j] = false;
        }
    }

    std::queue<std::pair<int, int>> q;

    q.push({ startX, startY });
    visited[startY][startX] = true;

    bool exitReached = false;
    std::vector<bool> itemsReached(itemPositions.size(), false);
    std::vector<bool> monstersReached(monsterPositions.size(), false);

    // 상하좌우 이동
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        // 출구에 도달했는지 확인
        if (x == exitX && y == exitY)
        {
            exitReached = true;
        }

        // 아이템에 도달했는지 확인
        for (size_t i = 0; i < itemPositions.size(); i++)
        {
            if (x == itemPositions[i].first && y == itemPositions[i].second)
            {
                itemsReached[i] = true;
            }
        }

        // 몬스터에 도달했는지 확인
        for (size_t i = 0; i < monsterPositions.size(); i++)
        {
            if (x == monsterPositions[i].first && y == monsterPositions[i].second)
            {
                monstersReached[i] = true;
            }
        }

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 맵 범위 체크
            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
            {
                // 방문하지 않았고 벽이 아닌 경우
                if (!visited[ny][nx] && outputMap->GetCellData(nx, ny) != DungeonTagTypes::Wall)
                {
                    visited[ny][nx] = true;
                    q.push({ nx, ny });
                }
            }
        }
    }

    // 출구, 모든 아이템, 모든 몬스터에 도달 가능한지 확인
    if (!exitReached)
    {
        // visited 메모리 해제
        for (int i = 0; i < height; i++)
        {
            delete[] visited[i];
        }
        delete[] visited;
        return false;
    }

    for (bool reached : itemsReached)
    {
        if (!reached)
        {
            // visited 메모리 해제
            for (int i = 0; i < height; i++)
            {
                delete[] visited[i];
            }
            delete[] visited;
            return false;
        }
    }

    for (bool reached : monstersReached)
    {
        if (!reached)
        {
            // visited 메모리 해제
            for (int i = 0; i < height; i++)
            {
                delete[] visited[i];
            }
            delete[] visited;
            return false;
        }
    }

    // visited 메모리 해제
    for (int i = 0; i < height; i++)
    {
        delete[] visited[i];
    }
    delete[] visited;

    return true;

}
//
//bool RandomMapGenerator::CanReachTarget(char** map, int width, int height, int startX, int startY, int targetX, int targetY)
//{
//    // 동적 2D 배열로 visited 생성
//    bool** visited = new bool*[height];
//    for (int i = 0; i < height; i++)
//    {
//        visited[i] = new bool[width];
//        for (int j = 0; j < width; j++)
//        {
//            visited[i][j] = false;
//        }
//    }
//
//    std::queue<std::pair<int, int>> q;
//
//    q.push({ startX, startY });
//    visited[startY][startX] = true;
//
//    bool exitReached = false;
//
//    // 상하좌우 이동
//    int dx[] = { 0, 0, -1, 1 };
//    int dy[] = { -1, 1, 0, 0 };
//
//    while (!q.empty())
//    {
//        auto [x, y] = q.front();
//        q.pop();
//
//        // 출구에 도달했는지 확인
//        if (x == targetX && y == targetY)
//        {
//            exitReached = true;
//        }
//
//        // 상하좌우 탐색
//        for (int i = 0; i < 4; i++)
//        {
//            int nx = x + dx[i];
//            int ny = y + dy[i];
//
//            // 맵 범위 체크
//            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
//            {
//                // 방문하지 않았고 벽이 아닌 경우
//                if (!visited[ny][nx] && map[ny][nx] != Const::Map::WALL)
//                {
//                    visited[ny][nx] = true;
//                    q.push({ nx, ny });
//                }
//            }
//        }
//    }
//
//    // 출구, 모든 아이템, 모든 몬스터에 도달 가능한지 확인
//    if (!exitReached)
//    {
//        // visited 메모리 해제
//        for (int i = 0; i < height; i++)
//        {
//            delete[] visited[i];
//        }
//        delete[] visited;
//        return false;
//    }
//
//
//    // visited 메모리 해제
//    for (int i = 0; i < height; i++)
//    {
//        delete[] visited[i];
//    }
//    delete[] visited;
//
//    return true;
//}
