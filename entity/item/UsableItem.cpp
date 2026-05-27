#include "UsableItem.h"

UsableItem::UsableItem(
    const std::string& n,
    const std::string& d,
    const std::string& id,
    std::shared_ptr<Command> cmd,
    ItemType type,
    int uses
): Item(n, d, id, type), useCommand(cmd), remainingUses(uses) {}

void UsableItem::use() {
    if (remainingUses == 0) {
        std::cout << "This item can no longer be used.\n";
        return;
    }

    if (useCommand) {
        useCommand->execute();
    }
    if (remainingUses > 0) {
        remainingUses--;
    }
    if (remainingUses == 0) {
        std::cout << "The item is now depleted.\n";
    }
};

bool UsableItem::isDepleted() const {
    return remainingUses == 0;
}

int UsableItem::getRemainingUses() const {
    return remainingUses;
}

void UsableItem::setUseCommand(std::shared_ptr<Command> cmd) {
    useCommand = cmd;
}