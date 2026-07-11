#include <iostream>
#include "GameManager.h"
#include "VirtualDisplay.h"
#include "Logger.h"
#include "ObjectManager.h"
#include "GameManagerBridge.h"
#include "Entity.h"

void main()
{
    auto bridgeEntity= ObjectManager::GetInstance().CreateEntity();

    shared_ptr<GameManager> gmPtr = make_shared<GameManager>();
    shared_ptr<GameManagerBridge::ConstructionParameter> bridgeParam
        = std::make_shared<GameManagerBridge::ConstructionParameter>(gmPtr);

    bridgeEntity->AddComponent<GameManagerBridge>(bridgeParam);

    while (true)
    {
        gmPtr->Update();
    
        Sleep(16);
    }
}