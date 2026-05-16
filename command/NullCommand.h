//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_NULLCOMMAND_H
#define ZOORK_NULLCOMMAND_H

#include "Command.h"
#include <iostream>

class NullCommand : public Command {
public:
    NullCommand() : Command(nullptr) {}

    void execute() override;
};


#endif //ZOORK_NULLCOMMAND_H
