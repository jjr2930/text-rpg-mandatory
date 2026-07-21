// VirtualDisplay.h 수정
#ifndef VIRUTAL_DISPLAY_H
#define VIRUTAL_DISPLAY_H

////////////////////////////////
/// START DISABLE WARNING 4005
////////////////////////////////

#pragma warning(push)
#pragma warning(disable: 4005) // Disable warning for deprecated functions

#define _HAS_STD_BYTE 0
#define WIN32_LEAN_AND_MEAN  // 추가
#include <Windows.h>

////////////////////////////////
/// END DISABLE WARNING 4005
////////////////////////////////

#pragma warning(pop)

#include "Vector2Int.h"
#include "Component.h"
#include "Enums.h"

#include <string>
#include <vector>

class AlchemyShop;
class InteractableObject;

using namespace std;

class VirtualDisplay : public Component
{
public:
    const Vector2Int INGAME_LOG_POSITION = Vector2Int(0, 20);
    
    const Vector2Int PLAYER_STATUS_POSITION = Vector2Int(50, 0);
    const string PLAYER_STATUS_TITLE = "===== Player Status =====";

    const Vector2Int INVENTORY_POSITION = Vector2Int(50, 10);
    const string INVENTORY_TITLE = "===== Inventory =====";

    const Vector2Int INTERACTION_POSITION = Vector2Int(80, 0);
    const string INTERACTION_TITLE = "===== Interaction =====";

    const int WIDTH = 120;
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
    void RenderIngame();
    void DrawChar(int x, int y, char character);
    void WriteString(int indexToWrite, int x, int y, const string& str);
    void HandleEvent(shared_ptr<EventParameter> message) override;

private:
    void ClearBuffer(int index);
    void Swap();
    bool FindDiff();

private:
    //double buffering;
    char** buffer[2];
    int currentBufferIndex;
    vector<DiffElement> diff;
    RenderMode drawMode;
    shared_ptr<InteractableObject> currentInteractableObject;

    HANDLE hConsole;
};

#endif // ! VIRUTAL_DISPLAY_H

