#include <iostream>
#include "GameManager.h"
#include "VirtualDisplay.h"
#include "Logger.h"
#include "ObjectManager.h"
#include "GameManagerBridge.h"
#include "Entity.h"
#include "TitleDrawer.h"

#include <format>

void main()
{
    TitleDrawer titleDrawer;
    titleDrawer.ProcessTitle();

    auto bridgeEntity= ObjectManager::GetInstance().CreateEntity();
    bridgeEntity->SetName("GameManagerBridgeEntity");

    shared_ptr<GameManager> gmPtr = make_shared<GameManager>();
    shared_ptr<GameManagerBridge::ConstructionParameter> bridgeParam
        = std::make_shared<GameManagerBridge::ConstructionParameter>(gmPtr);

    auto bridgeComponent = bridgeEntity->AddComponent<GameManagerBridge>(bridgeParam);
    bridgeComponent->SetName(format("{}'s GameManagerBridge", bridgeEntity->GetName()));

    while (true)
    {
        gmPtr->Update();
    
        Sleep(16);
    }
}