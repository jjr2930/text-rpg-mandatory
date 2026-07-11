#include "GameManagerBridge.h"
#include "EventParameter.h"
#include "GameManager.h"

void GameManagerBridge::HandleEvent(shared_ptr<EventParameter> message)
{
    gameManager->HandleEvent(message);
}
