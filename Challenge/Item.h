#ifndef ITEM_H
#define ITEM_H  
#include <string>

class MonsterDropItem;

class Item
{
public: 
    Item(std::string& name, int price);
    Item(MonsterDropItem& dropItem);
    /*
    * getter    
    */

    std::string GetName() const;
    int GetPrice() const;

private:
    std::string name;
    int price;
};

#endif // !ITEM_H