//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "../GameObject.h"
#include <memory>
#include <iostream>

enum class ItemType {
    Generic,
    Key,
    Equippable,
    Clue
};

class Item : public GameObject {
public:
    Item(const std::string &n, const std::string &d, const std::string &id, ItemType type);

    virtual ~Item() = default;

    virtual void use(); 

    ItemType getType() const;
    std::string getItemId() const;

protected:
    ItemType type;
    std::string itemId;
};

#endif //ZOORK_ITEM_H
