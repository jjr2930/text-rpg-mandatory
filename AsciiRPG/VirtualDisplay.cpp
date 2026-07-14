#include "VirtualDisplay.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Const.h"
#include "Logger.h"
#include "Player.h"
#include "InventoryItem.h"
#include "EventParameter.h"
#include "Enums.h"

#include <format>
#include <iostream>

using namespace std;

VirtualDisplay::VirtualDisplay(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
    , currentBufferIndex(0)
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
    RenderIngame();

    FindDiff();

    for (auto& d : diff)
    {
        DrawChar(d.position.x, d.position.y, d.character);
    }

    currentBufferIndex = (currentBufferIndex + 1) % 2;
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

        nextBuffer[pos.y][pos.x] = r->GetToPrint();
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
    shared_ptr<Player> player = ObjectManager::GetInstance().GetObjectsByType<Player>()[0];

    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y, PLAYER_STATUS_TITLE);
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 1, format("LV : {0}", player->GetLevel()));
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 2, format("EXP : {0}", player->GetExp()));
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 3, format("HP : {0}/{1}", player->GetCurrentHelath(), player->GetMaxHp()));
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 4, format("ATK : {0}", player->GetAttack()));
    WriteString(nextBufferIndex, PLAYER_STATUS_POSITION.x, PLAYER_STATUS_POSITION.y + 5, format("DEF : {0}", player->GetDefense()));

    //write inventory
    WriteString(nextBufferIndex, INVENTORY_POSITION.x, INVENTORY_POSITION.y, INVENTORY_TITLE);

    vector<InventoryItem> inventory = player->GetInventory();
    size = inventory.size();
    for (int i = 0; i < size; ++i)
    {
        if (player->GetInventoryCursorIndex() == i)
        {
            WriteString(nextBufferIndex, INVENTORY_POSITION.x, INVENTORY_POSITION.y + i + 1
                , format("> {0} x {1} <", inventory[i].GetName(), inventory[i].GetQuantity()));
        }
        else
        {
            WriteString(nextBufferIndex, INVENTORY_POSITION.x, INVENTORY_POSITION.y + i + 1
                , format("  {0} x {1}  ", inventory[i].GetName(), inventory[i].GetQuantity()));
        }
    }
}