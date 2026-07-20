#ifndef BOSS_MOVING_STATE_H
#define BOSS_MOVING_STATE_H

#include <memory>
#include <vector>

#include "State.h"
#include "Vector2Int.h"

using namespace std;

class Position;

class DragonMovingState :  public State
{
public:
    DragonMovingState(double movingDelay);

    void Start() override;
    void Update() override;
    bool IsArrived() const;
private:
    bool HasPlayerMoved() const;
    void PathfindToPlayer();
    bool IsTimeToMove() const;
    void SaveCurrentPlayerPosition();
    void MoveNextStepTowardsPlayer();
    
private :
    shared_ptr<Position> playerPosition;
    shared_ptr<Position> dragonPosition;

    Vector2Int lastPlayerPosition;
    vector<Vector2Int> currentPathToPlayer;
    int currentPathIndex = 0;
    double lastMovingTime = 0.0;
    double movingDelay;
};


#endif // !BOSS_MOVING_STATE_H