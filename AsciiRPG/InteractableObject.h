#ifndef INTERACTABLE_OBJECT_H
#define INTERACTABLE_OBJECT_H

#include "Component.h"
#include "Enums.h"

class InteractableObject : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, InteractableObjectTags tag)
            : Component::ConstructionParamterBase(entity)
            , tag(tag)
        {}
        InteractableObjectTags tag;
    };

public:
    using Component::Component;
    InteractableObject(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    //getter
    InteractableObjectTags GetTag();
    virtual vector<string> GetRenderStrings();

    //setter
    virtual void IncreaseCursorIndex();
    virtual void DecreaseCursorIndex();
    virtual void ConfirmSelection();
    virtual void OnCancel();
    virtual void Reset();
    virtual void OnDisable();

private:
    InteractableObjectTags tag;
};

#endif // !INTERACTABLE_OBJECT_H