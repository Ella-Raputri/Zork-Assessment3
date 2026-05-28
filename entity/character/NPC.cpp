#include "NPC.h"

NPC::NPC(
    const std::string& name,
    const std::string& description,
    const std::vector<std::string>& dialogue
): 
Character(name, description), posX(0), posY(0) {
    dialogueStages.push_back(dialogue); //stage 0
};

void NPC::talk() const {
    auto& lines = dialogueStages[currentStage];
    for (const auto& line: lines){
        std::cout << getName() << ": " << line << std::endl;
    }
};

void NPC::setDialogueStage(int stage) {
    if (stage < dialogueStages.size()) currentStage = stage;
}

void NPC::addDialogueStage(std::vector<std::string> lines) {
    dialogueStages.push_back(lines);
}

void NPC::setPosition(int x, int y){
    posX = x; posY = y;
}

int NPC::getX() const {
    return posX;
}
int NPC::getY() const {
    return posY;
}