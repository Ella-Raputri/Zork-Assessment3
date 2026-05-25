#include "NPC.h"

NPC::NPC(
    const std::string& name,
    const std::string& description,
    const std::vector<std::string>& dialogue
): 
Character(name, description), dialogueLines(dialogue), posX(0), posY(0) {};

void NPC::talk() const {
    for (const auto& line: dialogueLines){
        std::cout << getName() << ": " << line << std::endl;
    }
};

void NPC::setPosition(int x, int y){
    posX = x; posY = y;
}

int NPC::getX() const {
    return posX;
}
int NPC::getY() const {
    return posY;
}