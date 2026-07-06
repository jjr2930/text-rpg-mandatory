#include "Item.h"
#include "Monster.h"

Item::Item(std::string& name, int price)
    : name(name)
    , price(price)
{
}

Item::Item(MonsterDropItem& dropItem)
    : name(dropItem.GetName())
    , price(dropItem.GetPrice())
{}

std::string Item::GetName() const
{
    return name;
}

int Item::GetPrice() const
{
    return price;
}
