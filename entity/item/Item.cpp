#include "Item.h"

Item::Item(const std::string &n, const std::string &d, const std::string &id, ItemType type)
    : GameObject(n, d), type(type), itemId(id) {}

void Item::use() {
    std::cout << "Nothing happens.\n";
}

ItemType Item::getType() const {
    return type;
}

std::string Item::getItemId() const {
    return itemId;
}