#ifndef ZOORK_NPC_H
#define ZOORK_NPC_H

#include "Character.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class NPC : public Character {
public:
    NPC(
        const std::string& name,
        const std::string& description,
        const std::vector<std::string>& dialogue
    );

    void talk() const;

    void setPosition(int x, int y);
    int getX() const;
    int getY() const;

private:
    std::vector<std::string> dialogueLines;
    int posX, posY;
};

#endif