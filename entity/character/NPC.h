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
        const std::vector<std::vector<std::string>> dialogueStages
    );

    void talk() const;
    void setDialogueStage(int stage); 

private:
    int currentStage = 0;
    std::vector<std::vector<std::string>> dialogueStages;
};

#endif