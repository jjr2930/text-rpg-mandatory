#include <iostream>
#include "GameManager.h"
#include "VirtualDisplay.h"

void main()
{
    GameManager gm;
    VirtualDisplay vd;

    while (true)
    {
        gm.Update();
        vd.Render();

        Sleep(100);
    }
}