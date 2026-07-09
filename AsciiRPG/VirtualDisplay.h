// VirtualDisplay.h 수정
#ifndef VIRUTAL_DISPLAY_H
#define VIRUTAL_DISPLAY_H

#define _HAS_STD_BYTE 0
#define WIN32_LEAN_AND_MEAN  // 추가
#include <Windows.h>

#include "Vector2Int.h"
#include <vector>

using namespace std;

class VirtualDisplay
{
public:
    const Vector2Int LOG_POSITION = Vector2Int(60, 0);
    const int WIDTH = 80;
    const int HEIGHT = 20;
    const int SLEEP_TIME_MS = 16;

public:
    class DiffElement 
    {
    public:
        DiffElement(Vector2Int position, char character)
            : position(position), character(character) {}

        Vector2Int position;
        char character;
    };

public: 
    VirtualDisplay();
    ~VirtualDisplay();
    void Render();
    void DrawChar(int x, int y, char character);

private:
    void ClearBuffer(int index);
    void Swap();
    bool FindDiff();

private:
    //double buffering;
    char** buffer[2];
    int currentBufferIndex;
    vector<DiffElement> diff;

    HANDLE hConsole;
};

#endif // ! VIRUTAL_DISPLAY_H

