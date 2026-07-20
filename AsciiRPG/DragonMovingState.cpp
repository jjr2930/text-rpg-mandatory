#include <queue>
#include <stack>
#include <format>

#include "DragonMovingState.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Position.h"
#include "Dragon.h"
#include "GameTime.h"
#include "DungeonObjectTag.h"
#include "Logger.h"
#include "Entity.h"


DragonMovingState::DragonMovingState(double movingDelay)
    : movingDelay(movingDelay)
{
}

void DragonMovingState::Start()
{
    auto [player, playerPosition] = ObjectManager::GetInstance().GetComponentTuple<Player, Position>();
    auto [dragon, dragonPosition] = ObjectManager::GetInstance().GetComponentTuple<Dragon, Position>();
 
    this->playerPosition = playerPosition;
    this->dragonPosition = dragonPosition;
}

void DragonMovingState::Update()
{
    if (HasPlayerMoved())
    {
        PathfindToPlayer();
        SaveCurrentPlayerPosition();
    }

    if (IsTimeToMove())
    {
        MoveNextStepTowardsPlayer();
    }
}

bool DragonMovingState::IsArrived() const
{
    auto nowDragonPosition = dragonPosition->GetPosition();
    auto destination = currentPathToPlayer.back();

    int distance = abs(nowDragonPosition.x - destination.x) + abs(nowDragonPosition.y - destination.y);
    return distance == 0;
}

bool DragonMovingState::HasPlayerMoved() const
{
    if (lastPlayerPosition.x != playerPosition->GetX() || lastPlayerPosition.y != playerPosition->GetY())
    {
        return true;
    }
    return false;
}

void DragonMovingState::PathfindToPlayer()
{
    //very ineffective, but it is logically simple.

    auto tags = ObjectManager::GetInstance().GetComponentTupleVector<DungeonObjectTag, Position>();

    char map[Const::Map::DEFAULT_HEIGHT][Const::Map::DEFAULT_WIDTH]
        = { Const::Map::EMPTY };

    for (auto& [tag, position] : tags)
    {
        Vector2Int pos = position->GetPosition();
        map[pos.y][pos.x] = tag->GetTag();
    }

    //set player position;
    map[playerPosition->GetY()][playerPosition->GetX()] = Const::Map::PLAYER;

    bool visited[Const::Map::DEFAULT_HEIGHT][Const::Map::DEFAULT_WIDTH] = { false };
    Vector2Int parentMap[Const::Map::DEFAULT_HEIGHT][Const::Map::DEFAULT_WIDTH];
    for (auto y = 0; y < Const::Map::DEFAULT_HEIGHT; ++y)
    {
        for (auto x = 0; x < Const::Map::DEFAULT_WIDTH; ++x)
        {
            parentMap[y][x] = Vector2Int(-1, -1);
        }
    }

    bool found = false;

    queue<Vector2Int> q;

    Vector2Int endPoint = playerPosition->GetPosition();
    Vector2Int startPosition = dragonPosition->GetPosition();
    q.push(startPosition);

    while (q.size() > 0)
    {
        Vector2Int now = q.front();
        q.pop();
        visited[now.y][now.x] = true;

        if (now.x == endPoint.x && now.y == endPoint.y)
        {
            found = true;
            break;
        }

        Vector2Int directions[4] = {
            Vector2Int(0, -1), // Up
            Vector2Int(0, 1),  // Down
            Vector2Int(-1, 0), // Left
            Vector2Int(1, 0)   // Right
        };

        //get traverse neighbours
        for (const auto& dir : directions)
        {
            Vector2Int next = Vector2Int(now.x + dir.x, now.y + dir.y);
            if (next.x < 0 || next.x >= Const::Map::DEFAULT_WIDTH || next.y < 0 || next.y >= Const::Map::DEFAULT_HEIGHT)
            {
                continue; // Out of bounds
            }
            if (visited[next.y][next.x])
            {
                continue; // Already visited
            }
            char cell = map[next.y][next.x];
            if (cell == Const::Map::WALL || cell == Const::Map::DRAGON)
            {
                continue; // Not walkable
            }

            q.push(next);
            parentMap[next.y][next.x] = now;
        }
    }

    //reconstruct path
    if (found)
    {
        stack<Vector2Int> pathStack;
        Vector2Int current = endPoint;
        while (current.x != -1 && current.y != -1)
        {
            pathStack.push(current);
            current = parentMap[current.y][current.x];
        }
        currentPathToPlayer.clear();
        while (!pathStack.empty())
        {
            currentPathToPlayer.push_back(pathStack.top());
            pathStack.pop();
        }

        currentPathToPlayer.erase(currentPathToPlayer.begin()); // Remove the dragon's current position from the path
        currentPathToPlayer.erase(currentPathToPlayer.end() - 1); // Remove the next step towards the player from the path
    }

    //print path for debug
    Logger::LogInfo("Dragon path to player:");
    int pathSize = currentPathToPlayer.size();
    for (int i = 0; i < pathSize; ++i)
    {
        Vector2Int point = currentPathToPlayer[i];
        Logger::LogInfo(format("Step {}: ({}, {})", i, point.x, point.y));
    }
}

bool DragonMovingState::IsTimeToMove() const
{
    if(GameTime::GetTime() - lastMovingTime >= movingDelay)
    {
        return true;
    }
    return false;
}

void DragonMovingState::SaveCurrentPlayerPosition()
{
    lastPlayerPosition = playerPosition->GetPosition();
}

void DragonMovingState::MoveNextStepTowardsPlayer()
{
    if(currentPathIndex < currentPathToPlayer.size())
    {
        Vector2Int nextPoint = currentPathToPlayer[currentPathIndex];
        dragonPosition->SetPosition( 
            nextPoint.x, 
            nextPoint.y
        );

        Logger::LogInfo(format("Dragon moved to ({}, {})", nextPoint.x, nextPoint.y));
        currentPathIndex++;
        lastMovingTime = GameTime::GetTime();
    }
}