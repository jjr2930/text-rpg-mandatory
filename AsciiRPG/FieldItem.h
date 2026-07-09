#ifndef ITEM_H
#define ITEM_H

#include "Component.h"

class Position;

class FieldItem : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, const string& itemName, int quantity)
            : Component::ConstructionParamterBase(entity)
            , itemName(itemName)
            , quantity(quantity)
        {}
        string itemName;
        int quantity;
    };
public:
    using Component::Component;
    FieldItem(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    
    string GetItemName() const;
    int GetQuantity() const;

    void Update() override;
private:
    string itemName;
    int quantity;
    shared_ptr<Position> myPosition;
};
#endif // !ITEM_H

