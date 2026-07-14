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
        ConstructionParameter(shared_ptr<Entity> entity, int tableKey, int quantity)
            : Component::ConstructionParamterBase(entity)
            , tableKey(tableKey)
            , quantity(quantity)
        {}
        int tableKey;
        int quantity;
    };
public:
    using Component::Component;
    FieldItem(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    
    string GetName() const;
    int GetTableKey() const;
    int GetQuantity() const;

    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;
private:
    int tableKey;
    int quantity;
    shared_ptr<Position> myPosition;
};
#endif // !ITEM_H

