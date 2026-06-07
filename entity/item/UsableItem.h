#ifndef ZOORK_USABLEITEM_H
#define ZOORK_USABLEITEM_H

#include "Item.h"
#include <memory>

class UsableItem : public Item {
private:
    std::string executeMessage;
    int remainingUses;

public:
    UsableItem(
        const std::string& n,
        const std::string& d,
        const std::string& id,
        std::string msg = "",
        ItemType type = ItemType::Generic,
        int uses = -1
    );

    void use() override;

    bool isDepleted() const;
    int getRemainingUses() const;
};

#endif