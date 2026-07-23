#ifndef ITEM_H
#define ITEM_H

#include "Component.h"
#include "Enums.h"

class Position;

class FieldItem : public Component
{
public:
    class ConstructionParameter : public Component::ConstructionParamterBase
    {
    public:
        ConstructionParameter(shared_ptr<Entity> entity, int tableKey, ItemType itemType, int quantity)
            : Component::ConstructionParamterBase(entity)
            , tableKey(tableKey)
            , itemType(itemType)
            , quantity(quantity)
        {}

        //TODO:: consider about it can get IItem
        int tableKey;
        ItemType itemType;
        int quantity;
    };
public:
    using Component::Component;
    FieldItem(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    
    string GetName() const;
    int GetTableKey() const;
    int GetQuantity() const;
    ItemType GetItemType() const;

    void Update() override;
    void HandleEvent(shared_ptr<EventParameter> message) override;
private:
    /// <summary>
    /// TODO: tablekey and item key make tuple or struct or class to manage them together. Because they are used together in many cases.
    /// </summary>
    int tableKey;
    ItemType itemType;
    int quantity;
    shared_ptr<Position> myPosition;
};
#endif // !ITEM_H

