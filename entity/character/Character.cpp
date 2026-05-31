//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "Character.h"
#include "../../location/room/Room.h"
#include "../../location/room/NullRoom.h"

Character::Character(const std::string &n, const std::string &d) : 
    GameObject(n, d),
    posX(0),
    posY(0), 
    currentRoom(new NullRoom()) {}

void Character::setPosition(int newX, int newY) {
    posX = newX;
    posY = newY;
}

int Character::getX() const { 
    return posX; 
}

int Character::getY() const { 
    return posY; 
}

void Character::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Character::getCurrentRoom() const {
    return currentRoom;
}