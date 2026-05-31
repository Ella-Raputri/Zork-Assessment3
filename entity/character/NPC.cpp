#include "NPC.h"

NPC::NPC(
    const std::string& name,
    const std::string& description,
    const std::vector<std::vector<std::string>> dialogueStages
): 
Character(name, description), dialogueStages(dialogueStages) {};

void NPC::talk() const {
    auto& lines = dialogueStages[currentStage];
    for (const auto& line: lines){
        std::cout << getName() << ": " << line << std::endl;
    }
};

void NPC::setDialogueStage(int stage) {
    if (stage < dialogueStages.size()) currentStage = stage;
}