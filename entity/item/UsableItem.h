#ifndef ZOORK_USABLEITEM_H
#define ZOORK_USABLEITEM_H

#include "Item.h"
#include "../../command/Command.h"
#include <memory>

class UsableItem : public Item {
private:
    std::shared_ptr<Command> useCommand;
    int remainingUses;

public:
    UsableItem(
        const std::string& n,
        const std::string& d,
        const std::string& id,
        std::shared_ptr<Command> cmd,
        ItemType type = ItemType::Generic,
        int uses = -1
    );

    void use() override;

    bool isDepleted() const;
    int getRemainingUses() const;

    void setUseCommand(std::shared_ptr<Command> cmd);
};

#endif