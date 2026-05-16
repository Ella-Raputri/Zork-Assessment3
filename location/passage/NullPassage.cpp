//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "NullPassage.h"

// NullPassage::NullPassage(Room* from) : Passage("null", "Time is a flat circle.", from, from) {}
NullPassage::NullPassage(Room* from) 
    : Passage("null", "Time is a flat circle.", from, from, 0, 0, 0, 0) {}