//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "../Item.h"
#include "Character.h"
#include <vector>
#include <memory>
#include <iostream>

class Room;

class Player : public Character {
public:
    static Player *instance() { 
        // Note: lazy instantiation of the singleton Player object 
        if (!playerInstance) { 
            playerInstance = new Player(); 
        } 
        return Player::playerInstance; 
    }

    void setCurrentRoom(Room*);
    Room* getCurrentRoom() const;

    void setPosition(int newX, int newY); 
    int getX() const ;
    int getY() const ;

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemName);
    std::shared_ptr<Item> getItem(const std::string& itemName);
    void showInventory() const;

    void equipItem(const std::string& itemName);
    void unequipItem();
    std::shared_ptr<Item> getEquippedItem() const;
    bool hasEquipped(const std::string& itemId) const;

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
    static Player *playerInstance;
    Room* currentRoom;
    int posX, posY;
    std::vector<std::shared_ptr<Item>> inventory;
    std::shared_ptr<Item> equippedItem;

    Player();
};

#endif //ZOORK_PLAYER_H
