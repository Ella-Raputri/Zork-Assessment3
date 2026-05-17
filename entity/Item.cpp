//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "Item.h"

#include <utility>

Item::Item(const std::string &n, const std::string &d, const std::string &id,
    int uses, ItemType type) : 
    GameObject(n, d), useCommand(std::make_shared<NullCommand>()), 
    remainingUses(uses), type(type), itemId(id) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c, const std::string &id,
    int uses, ItemType type) : 
    GameObject(n, d), useCommand(std::move(c)), 
    remainingUses(uses), type(type), itemId(id) {}

void Item::use() {
    if (remainingUses == 0) {
        std::cout << "The item can no longer be used.\n";
        return;
    }
    if(remainingUses == 1){
        std::cout << "This will be the last time you can use it.\n";
    }

    useCommand->execute();

    if(remainingUses > 0){
        remainingUses--;
    }
}

bool Item::isDepleted() const {
    return remainingUses == 0;
}

int Item::getRemainingUses() const {
    return remainingUses;
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}

ItemType Item::getType() const {
    return type;
}

std::string Item::getItemId() const {
    return itemId;
}