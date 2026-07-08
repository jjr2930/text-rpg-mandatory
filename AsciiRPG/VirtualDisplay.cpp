#include "VirtualDisplay.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Const.h"
#include <iostream>

using namespace std;

VirtualDisplay::VirtualDisplay()
{
    buffer = new char* [Const::VirtualDisplay::HEIGHT];
    for (int i = 0; i < Const::VirtualDisplay::HEIGHT; ++i)
    {
        buffer[i] = new char[Const::VirtualDisplay::WIDTH];
    }
}

VirtualDisplay::~VirtualDisplay()
{
    for (int i = 0; i < Const::VirtualDisplay::HEIGHT; ++i)
    {
        delete[] buffer[i];
    }
    delete[] buffer;
}

void VirtualDisplay::Render()
{
    system("cls"); // Clear the console screen

    vector<shared_ptr<Renderer>> renderer = ObjectManager::GetInstance().GetObjectsByType<Renderer>();

    //clear buffer
    for (int i = 0; i < Const::VirtualDisplay::HEIGHT; ++i)
    {
        for (int j = 0; j < Const::VirtualDisplay::WIDTH; ++j)
        {
            buffer[i][j] = ' ';
        }
    }

    for (const auto& r : renderer)
    {
        Vector2Int pos = r->GetPosition();

        if (pos.x < 0 || pos.x >= Const::VirtualDisplay::WIDTH || pos.y < 0 || pos.y >= Const::VirtualDisplay::HEIGHT)
        {
            continue;
        }

        if (r->GetToPrint() == ' ')
        {
            continue;
        }

        buffer[pos.y][pos.x] = r->GetToPrint();
    }

    string displayText;

    for (int i = 0; i < Const::VirtualDisplay::HEIGHT; ++i)
    {
        for (int j = 0; j < Const::VirtualDisplay::WIDTH; ++j)
        {
            displayText += buffer[i][j];
        }
        displayText += '\n';
    }
    
    cout << displayText;
}
