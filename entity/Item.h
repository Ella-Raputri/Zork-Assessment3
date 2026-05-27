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
    Equippable
};

class Item : public GameObject {
public:
    Item(const std::string &n, const std::string &d, const std::string &id,
        int uses = -1, ItemType type = ItemType::Generic);

    Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, const std::string &id,
        int uses = -1, ItemType type = ItemType::Generic);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);
    bool isDepleted() const;
    int getRemainingUses() const;
    ItemType getType() const;
    std::string getItemId() const;

protected:
    std::shared_ptr<Command> useCommand;
    int remainingUses;
    ItemType type;
    std::string itemId;
};

#endif //ZOORK_ITEM_H
