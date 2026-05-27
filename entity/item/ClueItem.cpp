#include "ClueItem.h"

#include <iostream>

ClueItem::ClueItem(const std::string &n,
                   const std::string &d,
                   const std::string &id)
    : Item(n, d, id, ItemType::Clue) {}

void ClueItem::use() {
    std::cout << "This item is only a clue and cannot be used.\n";
}