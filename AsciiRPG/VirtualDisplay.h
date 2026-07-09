// VirtualDisplay.h 수정
#ifndef VIRUTAL_DISPLAY_H
#define VIRUTAL_DISPLAY_H

#define _HAS_STD_BYTE 0
#define WIN32_LEAN_AND_MEAN  // 추가
#include <Windows.h>

#include "Vector2Int.h"
#include "Component.h"

#include <string>
#include <vector>

using namespace std;

class VirtualDisplay : public Component
{
public: enum class DisplayMode
{
    Ingame,
    Inventory,
};

public:
    const Vector2Int INGAME_LOG_POSITION = Vector2Int(0, 20);
    
    const Vector2Int PLAYER_STATUS_POSITION = Vector2Int(50, 0);
    const string PLAYER_STATUS_TITLE = "===== Player Status =====";

    const Vector2Int INVENTORY_POSITION = Vector2Int(50, 10);
    const string INVENTORY_TITLE = "===== Inventory =====";

    const Vector2Int INVENTORY_LOG_POSITION = Vector2Int(50, 0);

    const int WIDTH = 100;
    const int HEIGHT = 30;
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
    using Component::Component;
    VirtualDisplay(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    ~VirtualDisplay();

    void Render();
    void DrawChar(int x, int y, char character);
    void WriteString(int indexToWrite, int x, int y, const string& str);

private:
    void ClearBuffer(int index);
    void Swap();
    bool FindDiff();
    void RenderIngame();

private:
    //double buffering;
    char** buffer[2];
    int currentBufferIndex;
    vector<DiffElement> diff;
    DisplayMode currentDisplayMode;

    HANDLE hConsole;
};

#endif // ! VIRUTAL_DISPLAY_H

