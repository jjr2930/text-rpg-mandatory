#include "VirtualDisplay.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Const.h"
#include <iostream>

using namespace std;

VirtualDisplay::VirtualDisplay()
    : currentBufferIndex(0)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);

    for (int i = 0; i < 2; ++i)
    {
        buffer[i] = new char* [Const::VirtualDisplay::HEIGHT];
        for (int j = 0; j < Const::VirtualDisplay::HEIGHT; ++j)
        {
            buffer[i][j] = new char[Const::VirtualDisplay::WIDTH];
        }
    }

    ClearBuffer(currentBufferIndex);
    ClearBuffer((currentBufferIndex + 1) % 2);

    system("cls"); // Clear the console screen
}

VirtualDisplay::~VirtualDisplay()
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < Const::VirtualDisplay::HEIGHT; ++j)
        {
            delete[] buffer[i][j];
        }
        delete[] buffer[i];
    }
}

void VirtualDisplay::Render()
{
    vector<shared_ptr<Renderer>> renderer = ObjectManager::GetInstance().GetObjectsByType<Renderer>();

    char** currentBuffer = buffer[currentBufferIndex];

    int nextBufferIndex = (currentBufferIndex + 1) % 2;
    
    ClearBuffer(nextBufferIndex);

    char** nextBuffer = buffer[nextBufferIndex];

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

        nextBuffer[pos.y][pos.x] = r->GetToPrint();
    }

    FindDiff();

    for (auto& d : diff)
    {
        DrawChar(d.position.x, d.position.y, d.character);
    }

    currentBufferIndex = nextBufferIndex;
}

void VirtualDisplay::DrawChar(int x, int y, char character)
{
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, pos);
    printf("%c", character);
}


void VirtualDisplay::ClearBuffer(int index)
{
    char** bufferToClear = buffer[index];
    for (int i = 0; i < Const::VirtualDisplay::HEIGHT; ++i)
    {
        for (int j = 0; j < Const::VirtualDisplay::WIDTH; ++j)
        {
            bufferToClear[i][j] = ' ';
        }
    }
}

void VirtualDisplay::Swap()
{
    currentBufferIndex = (currentBufferIndex + 1) % 2;
}

bool VirtualDisplay::FindDiff()
{
    diff.clear();
    int nextIndex = (currentBufferIndex + 1) % 2;

    char** currentBuffer = buffer[currentBufferIndex];
    char** nextBuffer = buffer[nextIndex];

    for (int i = 0; i < Const::VirtualDisplay::HEIGHT; ++i)
    {
        for (int j = 0; j < Const::VirtualDisplay::WIDTH; ++j)
        {
            if (currentBuffer[i][j] != nextBuffer[i][j])
            {
                diff.emplace_back(Vector2Int(j, i), nextBuffer[i][j]);
            }
        }
    }

    return diff.size() > 0;
}