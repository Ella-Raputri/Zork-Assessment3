//
// Created by Richard Skarbez on 5/7/23.
//

#include "PassageDefaultEnterCommand.h"

void PassageDefaultEnterCommand::execute() {
    auto* room = static_cast<Passage*>(gameObject)->getTo();
    std::cout << "Enter room: " << room->getName() << "\n"; // debug
    // std::cout << "Description: " << room->getDescription() << "\n"; // debug
    room->enter();
}