#include "VirtualDisplay.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Const.h"
#include "Logger.h"
#include "Player.h"
#include "InventoryItem.h"
#include "EventParameter.h"
#include "Enums.h"
#include "InteractableObject.h"
#include "GearTable.h"

#include <format>
#include <iostream>

using namespace std;

VirtualDisplay::VirtualDisplay(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , currentBufferIndex(0)
    , drawMode(RenderMode::Ingame)
    , currentInteractableObject(nullptr)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);

    for (int i = 0; i < 2; ++i)
    {
        buffer[i] = new char* [HEIGHT];
        for (int j = 0; j < HEIGHT; ++j)
        {
            buffer[i][j] = new char[WIDTH];
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
        for (int j = 0; j < HEIGHT; ++j)
        {
            delete[] buffer[i][j];
        }
        delete[] buffer[i];
    }
}

void VirtualDisplay::Render()
{
    switch (drawMode)
    {
        case RenderMode::None:
            break;
        case RenderMode::Ingame:
            RenderIngame(); 
            break;
        default:
            break;
    }

}

void VirtualDisplay::DrawChar(int x, int y, char character)
{
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, pos);
    printf("%c", character);
}

void VirtualDisplay::WriteString(int indexToWrite, int x, int y, const string& str)
{
    if (y >= HEIGHT || y < 0)
    {
        return;
    }

    char** bufferToWrite = buffer[indexToWrite];
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (x + i < WIDTH)
        {
            bufferToWrite[y][x + i] = str[i];
        }
    }
}
void VirtualDisplay::HandleEvent(shared_ptr<EventParameter> message)
{
    switch (message->eventType)
    {
        case EventType::OnStartInteraction:
            {
                InteractionStartEventParameter* interactMessage = static_cast<InteractionStartEventParameter*>(message.get());
                currentInteractableObject = interactMessage->interactableObject;
            }
            break;

        case EventType::OnStopInteraction:
            {
                currentInteractableObject = nullptr;
            }
            break;
        default:
            break;
    }
}

void VirtualDisplay::ClearBuffer(int index)
{
    char** bufferToClear = buffer[index];
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
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

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (currentBuffer[i][j] != nextBuffer[i][j])
            {
                diff.emplace_back(Vector2Int(j, i), nextBuffer[i][j]);
            }
        }
    }

    return diff.size() > 0;
}

void VirtualDisplay::RenderIngame()
{
    shared_ptr<Player> player = ObjectManager::GetInstance().GetObjectsByType<Player>()[0];

    vector<shared_ptr<Renderer>> renderer = ObjectManager::GetInstance().GetObjectsByType<Renderer>();

    char** currentBuffer = buffer[currentBufferIndex];

    int nextBufferIndex = (currentBufferIndex + 1) % 2;

    ClearBuffer(nextBufferIndex);

    char** nextBuffer = buffer[nextBufferIndex];

    //write main game images;
    for (const auto& r : renderer)
    {
        Vector2Int pos = r->GetPosition();

        if (pos.x < 0 || pos.x >= WIDTH || pos.y < 0 || pos.y >= HEIGHT)
        {
            continue;
        }

        if (nextBuffer[pos.y][pos.x] == 'P')
        {
            continue;
        }

        char toPrint = r->GetToPrint();
        nextBuffer[pos.y][pos.x] = toPrint;
    }

    //write main game guide
    if(player->GetCurrentInputMode() == Player::CurrentInputMode::Ingame)
    {
        WriteString(nextBufferIndex, INGAME_GUIDE_POSITION.x, INGAME_GUIDE_POSITION.y, "'Arrow':Move, 'I':Inventory, 'E':Interact");
    }

    //write recently logged messages
    auto logs = Logger::GetInstance().GetRecentLogs();
    int size = logs.size();

    if (size > 10)
    {
        Logger::LogError("Recent logs count must be 10");
    }

    for (int i = 0; i < size; ++i)
    {
        const string& log = *next(logs.begin(), i);
        int x = INGAME_LOG_POSITION.x;
        int y = INGAME_LOG_POSITION.y + i;
        if (y < 0 || y >= HEIGHT)
        {
            continue;
        }

        WriteString(nextBufferIndex, x, y, log);
    }

    //write player status
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y, PLAYER_STATUS_TITLE);
    
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 1
        , format("LV : {0}", player->GetLevel()));
    
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 2
        , format("EXP : {0} +{1}", player->GetExp(), player->GetAddedStat(StatType::Exp)));
    
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 3
        , format("HP : {0}/({1} +{2})", player->GetCurrentHealth(), player->GetMaxHealth(), player->GetAddedStat(StatType::MaxHealth)));
    
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 4
        , format("ATK : {0} +{1}", player->GetAttack(), player->GetAddedStat(StatType::Attack)));
    
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 5
        , format("DEF : {0} +{1}", player->GetDefense(), player->GetAddedStat(StatType::Defense)));

    //write gear
    WriteString(nextBufferIndex, GEAR_START_POSITION.x, GEAR_START_POSITION.y, GEAR_TITLE);

    const auto& equippedGear = player->GetEquippedGear();
    int gearIndex = 0;
    for (const auto& [slot, item] : equippedGear)
    {
        WriteString(nextBufferIndex, GEAR_START_POSITION.x, GEAR_START_POSITION.y + gearIndex + 1
            , item.GetName());

        gearIndex++;
    }

    //write inventory
    vector<string> inventoryString = player->GetInventoryRenderStrings();
    WriteString(nextBufferIndex, INVENTORY_POSITION.x, INVENTORY_POSITION.y, INVENTORY_TITLE);

    size = inventoryString.size();
    for (int i = 0; i < size; ++i)
    {
        WriteString(nextBufferIndex, INVENTORY_POSITION.x, INVENTORY_POSITION.y + i + 1, inventoryString[i]);
    }

    //write interaction
    WriteString(nextBufferIndex, INTERACTION_POSITION.x, INTERACTION_POSITION.y, INTERACTION_TITLE);
    if (nullptr != currentInteractableObject)
    {
        auto renderStrings = currentInteractableObject->GetRenderStrings();
        for (int i = 0; i < renderStrings.size(); ++i)
        {
            WriteString(nextBufferIndex, INTERACTION_POSITION.x, INTERACTION_POSITION.y + i + 1, renderStrings[i]);
        }
    }

    //
    FindDiff();

    for (auto& d : diff)
    {
        DrawChar(d.position.x, d.position.y, d.character);
    }

    currentBufferIndex = (currentBufferIndex + 1) % 2;
}