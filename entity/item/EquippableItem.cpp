#include "EquippableItem.h"

EquippableItem::EquippableItem(
    const std::string& n,
    const std::string& d,
    const std::string& id,
    const std::vector<std::string>& requiredRegions
)
    : Item(n, d, id, ItemType::Equippable),
      equipped(false),
      requiredRegions(requiredRegions)
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

void EquippableItem::use() {
    std::cout << "This item must be equipped, not used.\n";
}

bool EquippableItem::isRequiredRegion(const std::string& region) const {
    return std::find(
        requiredRegions.begin(),
        requiredRegions.end(),
        region
    ) != requiredRegions.end();
}