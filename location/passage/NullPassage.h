//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_NULLPASSAGE_H
#define ZOORK_NULLPASSAGE_H

#include "Passage.h"
#include "../room/Room.h"
#include <memory>

class NullPassage : public Passage {
public:
    explicit NullPassage(Room*);
};


#endif //ZOORK_NULLPASSAGE_H
