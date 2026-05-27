#include "EquippableItem.h"
#include <iostream>

EquippableItem::EquippableItem(
    const std::string& n,
    const std::string& d,
    const std::string& id,
    const std::string& requiredRegion
)
    : Item(n, d, id, ItemType::Equippable),
      equipped(false),
      requiredRegion(requiredRegion)
{}

void EquippableItem::equip() {
    if (equipped) {
        std::cout << "Already equipped.\n";
        return;
    }
    equipped = true;
}

void EquippableItem::unequip() {
    if (!equipped) {
        std::cout << "Not equipped.\n";
        return;
    }
    equipped = false;
}

bool EquippableItem::isEquipped() const {
    return equipped;
}

std::string EquippableItem::getRequiredRegion() const {
    return requiredRegion;
}

void EquippableItem::use() {
    std::cout << "This item must be equipped, not used.\n";
}