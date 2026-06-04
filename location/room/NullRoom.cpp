//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "../../command/NullCommand.h"
#include "NullRoom.h"

// NullRoom::NullRoom() : Room("Nowhere", "This is a nonplace.", std::make_shared<NullCommand>()) {}
NullRoom::NullRoom() : Room("Nowhere", "This is a nonplace.", 10, 10, 10, 10) {}