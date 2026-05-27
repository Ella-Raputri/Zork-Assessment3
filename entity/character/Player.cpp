//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "Player.h"
#include "../../location/room/NullRoom.h"

Player::Player()
    : Character(
        "You",
        "You are a person, alike in dignity to any other, but uniquely you."
    ),
    currentRoom(new NullRoom()),
    posX(0),
    posY(0)
{}

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}

void Player::setPosition(int newX, int newY) {
    posX = newX;
    posY = newY;
}

int Player::getX() const { 
    return posX; 
}

int Player::getY() const { 
    return posY; 
}

void Player::addItem(std::shared_ptr<Item> item){
    inventory.push_back(item);
}

void Player::removeItem(const std::string& itemName){
    for(auto it = inventory.begin(); it != inventory.end(); it++){
        if ((*it)->getName() == itemName) {
            inventory.erase(it);
            return;
        }
    }
    std::cout << "No " << itemName << " found in the inventory." << std::endl;
}

std::shared_ptr<Item> Player::getItem(const std::string& itemName){
    for (auto &item : inventory) {
        if (item->getName() == itemName) {
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
        int uses = item->getRemainingUses();

        if (uses > 0) {
            std::cout << " (" << uses << " uses left)";
        }
        std::cout << "\n";
    }
}