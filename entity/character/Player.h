//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "../item/Item.h"
#include "../item/UsableItem.h"
#include "../item/EquippableItem.h"
#include "Character.h"
#include <vector>
#include <memory>
#include <iostream>

class Player : public Character {
public:
    static Player *instance() { 
        // Note: lazy instantiation of the singleton Player object 
        if (!playerInstance) { 
            playerInstance = new Player(); 
        } 
        return Player::playerInstance; 
    }

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemId, const std::string& itemName);
    std::shared_ptr<Item> getItemByName(const std::string& itemName);
    std::shared_ptr<Item> getItemById(const std::string& itemId);
    void showInventory() const;

    void equipItem(const std::string& itemName);
    void unequipItem();
    std::shared_ptr<EquippableItem> getEquippedItem() const;
    bool hasEquipped(const std::string& itemId) const;
    void checkEquippedRegion();

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    std::vector<std::shared_ptr<Item>> inventory;
    std::shared_ptr<EquippableItem> equippedItem;

    Player();
};

#endif //ZOORK_PLAYER_H
