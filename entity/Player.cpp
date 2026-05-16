//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

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
