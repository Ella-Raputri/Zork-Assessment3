//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "../GameObject.h"
#include <vector>

class Room;
class Character : public GameObject {
public:
    Character(const std::string &, const std::string &);
    void setPosition(int newX, int newY); 
    int getX() const ;
    int getY() const ;

    void setCurrentRoom(Room*);
    Room* getCurrentRoom() const;

protected:
    int posX, posY;
    Room* currentRoom;
//    std::vector<Item*> inventory;
//    std::vector<std::string> tags;
//    int health;
//    int attack;
//    int move;
//    int initiative;
};

#endif //ZOORK_CHARACTER_H
