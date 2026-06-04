//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "PassageDefaultEnterCommand.h"

void PassageDefaultEnterCommand::execute() {
    auto* room = static_cast<Passage*>(gameObject)->getTo();
    std::cout << "Enter room: " << room->getName() << "\n";
    room->enter();
}