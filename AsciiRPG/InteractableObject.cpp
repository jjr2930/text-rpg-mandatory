#include "InteractableObject.h"

InteractableObject::InteractableObject(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params)
    : Component(id, name, params)
{
    auto constructionParams = std::static_pointer_cast<ConstructionParameter>(params);
    tag = constructionParams->tag;
}

InteractableObjectTags InteractableObject::GetTag()
{
    return tag;
}

vector<string> InteractableObject::GetRenderStrings()
{
    return vector<string>();
}

void InteractableObject::IncreaseCursorIndex(){}
void InteractableObject::DecreaseCursorIndex(){}
void InteractableObject::ConfirmSelection(){}
void InteractableObject::OnCancel(){}
void InteractableObject::Reset(){}
void InteractableObject::OnDisable(){}
