#ifndef GAME_TIME_H
#define GAME_TIME_H

#include "SingletonMacro.h"
#include <chrono>   

using namespace std;

class GameTime
{
public :
    SINGLETON_WITH_INIT(GameTime)

public:
    static double GetTime();

private:
    double OnGetTime() const;
    void Init();

private:
    chrono::high_resolution_clock::time_point start;
};

#endif // !GAME_TIME_H

