#ifndef ZOORK_EQUIPPABLEITEM_H
#define ZOORK_EQUIPPABLEITEM_H

#include "Item.h"

class EquippableItem : public Item {
private:
    bool equipped;
    std::string requiredRegion;

public:
    EquippableItem(
        const std::string& n,
        const std::string& d,
        const std::string& id,
        const std::string& requiredRegion = ""
    );

    void equip();
    void unequip();

    bool isEquipped() const;
    std::string getRequiredRegion() const;

    void use() override; 
};

#endif