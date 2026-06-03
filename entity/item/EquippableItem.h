#ifndef ZOORK_EQUIPPABLEITEM_H
#define ZOORK_EQUIPPABLEITEM_H

#include "Item.h"
#include <vector>
#include <algorithm>

class EquippableItem : public Item {
private:
    bool equipped;
    std::vector<std::string> requiredRegion;

public:
    EquippableItem(
        const std::string& n,
        const std::string& d,
        const std::string& id,
        const std::vector<std::string>& requiredRegion = {}
    );

    void equip();
    void unequip();

    bool isEquipped() const;
    const std::vector<std::string>& getRequiredRegion();
    bool isRequiredRegion(const std::string& region) const;

    void use() override; 
};

#endif