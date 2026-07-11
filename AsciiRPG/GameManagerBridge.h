#pragma once
#include "Component.h"
#include "IConstructionParameter.h"

class GameManager;

class GameManagerBridge :    public Component
{
public :
    class  ConstructionParameter : public IConstructionParameter
    {
    public:
        ConstructionParameter(shared_ptr<GameManager> gameManager)
            : IConstructionParameter()
            , gameManager(gameManager)
        {
        }

        shared_ptr<GameManager> gameManager;
    };

public:
    GameManagerBridge(int64_t id, const std::string& name, shared_ptr<IConstructionParameter> params)
        : Component(id, name, params)
    {
        auto constructionParams = static_cast<ConstructionParameter*>(params.get());
        
        this->gameManager = constructionParams->gameManager;
    }

    void HandleEvent(shared_ptr<EventParameter> message) override;
private:
    shared_ptr<GameManager> gameManager;

};

