//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "../room/NullRoom.h"
#include "../room/Room.h"
#include <iostream>
#include <utility>

class Passage : public Location {
public:
    static void createBasicPassage(Room* from, Room* to,
                               const std::string &direction,
                               int fromDoorX, int fromDoorY,
                               int toDoorX,   int toDoorY,
                               int fromArriveX, int fromArriveY,
                               int toArriveX,   int toArriveY,
                               bool bidirectional = true);

    Passage(const std::string &n, const std::string &d,
        Room* from, Room* to,
        int doorX,   int doorY,
        int arriveX, int arriveY);

    void setFrom(Room*);
    Room* getFrom() const;
    void setTo(Room*);
    Room* getTo() const;

    int getDoorX() const;
    int getDoorY() const;
    int getArriveX() const;
    int getArriveY() const;

protected:
    static std::string oppositeDirection(const std::string &);

    Room* fromRoom;
    Room* toRoom;
    int doorX, doorY;
    int arriveX, arriveY;
};

#endif //ZOORK_PASSAGE_H
