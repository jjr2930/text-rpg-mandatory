#include <iostream>
#include "GameManager.h"
#include "VirtualDisplay.h"
#include "Logger.h"

void main()
{
    for (int i = 0; i < 20; ++i)
    {
        Logger::LogInfo("Test");
    }

    GameManager gm;

    while (true)
    {
        gm.Update();
    
        Sleep(16);
    }
}