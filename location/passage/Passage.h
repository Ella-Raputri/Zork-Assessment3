//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "../room/NullRoom.h"
#include "../room/Room.h"
#include <iostream>

class Passage : public Location {
public:
    static void createBasicPassage(Room* from, Room* to,
                                   const std::string &direction,
                                   int fromX, int fromY,   
                                   int toX,   int toY,     
                                   bool bidirectional = true);

    Passage(const std::string &n, const std::string &d,
            Room* from, Room* to,
            int fromX, int fromY,
            int toX,   int toY);

    // Passage(const std::string &, const std::string &, std::shared_ptr<Command>, Room*, Room*);

    void setFrom(Room*);
    Room* getFrom() const;
    void setTo(Room*);
    Room* getTo() const;

    int getFromX() const;
    int getFromY() const;
    int getToX() const;
    int getToY() const;

protected:
    static std::string oppositeDirection(const std::string &);

    Room* fromRoom;
    Room* toRoom;
    int fromX, fromY;
    int toX, toY;
};

#endif //ZOORK_PASSAGE_H
