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
    void setDialogueStage(int stage); 
    void addDialogueStage(std::vector<std::string> lines);

    void setPosition(int x, int y);
    int getX() const;
    int getY() const;

private:
    int currentStage = 0;
    std::vector<std::vector<std::string>> dialogueStages;
    int posX, posY;
};

#endif