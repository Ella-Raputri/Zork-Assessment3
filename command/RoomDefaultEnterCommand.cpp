//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "RoomDefaultEnterCommand.h"

void RoomDefaultEnterCommand::execute() {
    std::cout << gameObject->getDescription() << "\n";
}