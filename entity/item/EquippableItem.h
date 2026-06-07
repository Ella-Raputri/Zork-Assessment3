#ifndef ZOORK_EQUIPPABLEITEM_H
#define ZOORK_EQUIPPABLEITEM_H

#include "Item.h"
#include <vector>
#include <algorithm>
#include <iostream>

class EquippableItem : public Item {
private:
    bool equipped;
    std::vector<std::string> requiredRegions;

public:
    EquippableItem(
        const std::string& n,
        const std::string& d,
        const std::string& id,
        const std::vector<std::string>& requiredRegions = {}
    );

    void equip();
    void unequip();

    bool isEquipped() const;
    bool isRequiredRegion(const std::string& region) const;

    void use() override; 
};

#endif