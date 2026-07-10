#include <iostream>
#include <random>
#include <string>
#include <queue>
#include <vector>

#include <iostream>
#include <random>
#include <string>
#include <queue>
#include <vector>

// 맵 요소 상수
const char WALL = '#';
const char START = 'S';
const char EXIT = 'X';
const char ITEM = '*';
const char EMPTY = ' ';
const float WALL_RATE = 0.15f;

// BFS를 사용하여 시작점에서 출구까지 경로가 있는지 확인
bool CanReachExit(char map[][40], int width, int height, int startX, int startY, int exitX, int exitY)
{
    bool visited[20][40] = { false };
    std::queue<std::pair<int, int>> q;

    q.push({ startX, startY });
    visited[startY][startX] = true;

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
            return true;
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
                if (!visited[ny][nx] && map[ny][nx] != WALL)
                {
                    visited[ny][nx] = true;
                    q.push({ nx, ny });
                }
            }
        }
    }

    return false;
}

void Clear(char**& map, int width, int height)
{
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            map[y][x] = ' ';
        }
    }
}

int main()
{
    const int MAP_WIDTH = 40;
    const int MAP_HEIGHT = 20;

    char map[MAP_HEIGHT][MAP_WIDTH];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(1, MAP_WIDTH - 2);
    std::uniform_int_distribution<> disY(1, MAP_HEIGHT - 2);
    std::uniform_int_distribution<> disChance(0, 100);

    bool loop = true;
    while (loop)
    {
        bool validMap = false;
        int startX, startY, exitX, exitY;

        // 유효한 맵이 생성될 때까지 반복
        while (!validMap)
        {
            // 맵 초기화
            for (int y = 0; y < MAP_HEIGHT; y++)
            {
                for (int x = 0; x < MAP_WIDTH; x++)
                {
                    map[y][x] = EMPTY;
                }
            }

            // 테두리 벽 생성
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                map[0][x] = WALL;
                map[MAP_HEIGHT - 1][x] = WALL;
            }
            for (int y = 0; y < MAP_HEIGHT; y++)
            {
                map[y][0] = WALL;
                map[y][MAP_WIDTH - 1] = WALL;
            }

            // 랜덤 내부 벽 생성 (전체 내부 공간의 30% 미만)
            int innerWidth = MAP_WIDTH - 2;
            int innerHeight = MAP_HEIGHT - 2;
            int totalInnerCells = innerWidth * innerHeight;
            int maxWalls = static_cast<int>(totalInnerCells * WALL_RATE) - 1; // WALL_RATE 미만

            // 랜덤하게 벽 배치
            for (int i = 0; i < maxWalls; i++)
            {
                int wallX, wallY;
                do
                {
                    wallX = disX(gen);
                    wallY = disY(gen);
                } while (map[wallY][wallX] != EMPTY); // 빈 공간에만 배치

                map[wallY][wallX] = WALL;
            }

            // 시작 지점(S) 배치
            do
            {
                startX = disX(gen);
                startY = disY(gen);
            } while (map[startY][startX] != EMPTY);
            map[startY][startX] = START;

            // 출구(X) 배치
            do
            {
                exitX = disX(gen);
                exitY = disY(gen);
            } while (map[exitY][exitX] != EMPTY);
            map[exitY][exitX] = EXIT;

            // 아이템(*) 배치 (5개)
            for (int i = 0; i < 5; i++)
            {
                int itemX, itemY;
                do
                {
                    itemX = disX(gen);
                    itemY = disY(gen);
                } while (map[itemY][itemX] != EMPTY); // 빈 공간에만 배치

                map[itemY][itemX] = ITEM;
            }

            // 시작 지점에서 출구까지 경로가 있는지 확인
            if (CanReachExit(map, MAP_WIDTH, MAP_HEIGHT, startX, startY, exitX, exitY))
            {
                validMap = true;
                std::cout << "유효한 맵 생성 완료!\n\n";
            }
            else
            {
                std::cout << "경로 없음, 맵 재생성 중...\n";
            }
        }

        // 맵 출력
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                std::cout << map[y][x];
            }
            std::cout << '\n';
        }

        // 사용자 입력
        std::cout << "\n새 맵을 생성하려면 Enter, 종료하려면 q를 입력하세요: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "q" || input == "Q")
        {
            loop = false;
        }

        std::cout << "\n\n";
    }
}