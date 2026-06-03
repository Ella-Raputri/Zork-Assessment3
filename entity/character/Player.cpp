//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "Player.h"
#include "../../location/room/Room.h"

Player::Player()
    : Character(
        "You",
        "\nYou are Pint, a researcher in this remote laboratory complex in the 18th eras. The only thing you remember before being unconscious is a violent earthquake that struck the facility, knocking everyone down at once. Most of your memories from last night are blurry.\nYou saw your colleague and friend, Chil, beside you. He seems to have also just regained consciousness.\n\nTalk to Chil to learn more about last night's situation."
    )
{}

Player *Player::playerInstance = nullptr;

void Player::addItem(std::shared_ptr<Item> item){
    inventory.push_back(item);
}

void Player::removeItem(const std::string& itemId, const std::string& itemName){
    for(auto it = inventory.begin(); it != inventory.end(); it++){
        if ((*it)->getItemId() == itemId) {
            inventory.erase(it);
            return;
        }
    }
    std::cout << "No " << itemName << " found in the inventory." << std::endl;
}

std::shared_ptr<Item> Player::getItemByName(const std::string& itemName){
    for (auto &item : inventory) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Player::getItemById(const std::string& itemId){
    for (auto &item : inventory) {
        if (item->getItemId() == itemId) {
            return item;
        }
    }
    return nullptr;
}

void Player::showInventory() const {
    if(inventory.empty()){
        std::cout << "Inventory is empty." << std::endl;
        return;
    }

    std::cout << "Inventory: " << std::endl;
    for (const auto &item : inventory) {
        std::cout << "- " << item->getName();

        auto usable = std::dynamic_pointer_cast<UsableItem>(item);
        if (usable) {
            int uses = usable->getRemainingUses();
            if (uses > 0) {
                std::cout << " (" << uses << " uses left)";
            }else{
                std::cout << " (unlimited uses)";
            }
        }
        else if(item->getType() == ItemType::Clue) {
            std::cout << " (cant be used or equipped. Description: " << item->getDescription() << ")";
        }
        else{
            std::cout << " (need to be equipped)";
        }
        std::cout << "\n";
    }
}

void Player::equipItem(const std::string& itemName){
    auto item = getItemByName(itemName);

    if (!item) {
        std::cout << "You don't have " << itemName << " in your inventory.\n";
        return;
    }

    auto equippable = std::dynamic_pointer_cast<EquippableItem>(item);
    if (!equippable) {
        std::cout << "You cannot equip this item.\n";
        return;
    }

    if (equippedItem) {
        unequipItem();
    }

    equippedItem = equippable;
    equippedItem->equip();
    removeItem(item->getItemId(), itemName);
    std::cout << "You equip " << itemName << ".\n";
}

void Player::unequipItem(){
    if(!equippedItem){
        std::cout << "Nothing is currently equipped.\n";
        return;
    }

    auto cell = currentRoom->getCell(posX, posY);
    if (equippedItem->isRequiredRegion(cell->getRegionTag())){
        std::cout << "You can not unequip your "  << equippedItem->getName() << " here.\n";
        return;
    }

    equippedItem->unequip();
    std::cout << "You unequip " << equippedItem->getName() << ".\n";

    addItem(equippedItem);
    equippedItem = nullptr;
}

std::shared_ptr<EquippableItem> Player::getEquippedItem() const {
    return equippedItem;
}

bool Player::hasEquipped(const std::string& itemId) const {
    return equippedItem && equippedItem->getItemId() == itemId;
}

void Player::checkEquippedRegion() {
    if (!equippedItem) return;

    auto cell = currentRoom->getCell(posX, posY);

    if (!equippedItem->isRequiredRegion(cell->getRegionTag())) {
        std::cout
            << "You are no longer in a region requiring "
            << equippedItem->getName()
            << ". Consider unequipping "
            << equippedItem->getName()
            << ".\n";
    }
}