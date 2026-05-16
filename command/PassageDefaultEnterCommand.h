//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_PASSAGEDEFAULTENTERCOMMAND_H
#define ZOORK_PASSAGEDEFAULTENTERCOMMAND_H


#include "Command.h"
#include "../location/passage/Passage.h"

#include <utility>

class PassageDefaultEnterCommand : public Command {
public:
    explicit PassageDefaultEnterCommand(GameObject* g) : Command(g) {}

    void execute() override;
};


#endif //ZOORK_PASSAGEDEFAULTENTERCOMMAND_H
