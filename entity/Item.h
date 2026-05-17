//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "../command/Command.h"
#include "GameObject.h"
#include "../command/NullCommand.h"
#include <memory>

enum class ItemType {
    Generic,
    Key,
    Consumable
};

class Item : public GameObject {
public:
    Item(const std::string &n, const std::string &d, int uses = -1, ItemType type = ItemType::Generic);

    Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, int uses = -1, ItemType type = ItemType::Generic);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);
    bool isDepleted() const;
    int getRemainingUses() const;
    ItemType getType() const;

protected:
    std::shared_ptr<Command> useCommand;
    int remainingUses;
    ItemType type;
};

#endif //ZOORK_ITEM_H
