//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "Passage.h"
#include "../../command/PassageDefaultEnterCommand.h"

std::string Passage::oppositeDirection(const std::string &s) {
    if (s == "north") return "south";
    else if (s == "south") return "north";
    else if (s == "east") return "west";
    else if (s == "west") return "east";
    else if (s == "up") return "down";
    else if (s == "down") return "up";
    else if (s == "in") return "out";
    else if (s == "out") return "in";
    else return "unknown_direction";
}

void Passage::createBasicPassage(Room* from, Room* to,
                                 const std::string &direction,
                                 int fromDoorX, int fromDoorY,
                                 int toDoorX,   int toDoorY,
                                 int fromArriveX, int fromArriveY,
                                 int toArriveX,   int toArriveY,
                                 bool bidirectional) {
    std::string name1 = from->getName() + "_to_" + to->getName();
    auto p1 = std::make_shared<Passage>(name1, "A totally normal passageway.",
                                        from, to,
                                        fromDoorX, fromDoorY,
                                        toArriveX, toArriveY);
    from->addPassage(direction, p1);

    if (bidirectional) {
        std::string name2 = to->getName() + "_to_" + from->getName();
        auto p2 = std::make_shared<Passage>(name2, "A totally normal passageway.",
                                            to, from,
                                            toDoorX, toDoorY,
                                            fromArriveX, fromArriveY);
        to->addPassage(oppositeDirection(direction), p2);
    }
}

Passage::Passage(const std::string &n, const std::string &d,
                 Room* from, Room* to,
                 int doorX, int doorY,
                 int arriveX, int arriveY)
    : Location(n, d), fromRoom(from), toRoom(to),
      doorX(doorX), doorY(doorY),
      arriveX(arriveX), arriveY(arriveY) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

void Passage::setFrom(Room* r) {
    fromRoom = r;
}

Room* Passage::getFrom() const {
    return fromRoom;
}

void Passage::setTo(Room* r) {
    toRoom = r;
}

Room* Passage::getTo() const {
    return toRoom;
}

int Passage::getDoorX()   const { return doorX; }
int Passage::getDoorY()   const { return doorY; }
int Passage::getArriveX() const { return arriveX; }
int Passage::getArriveY() const { return arriveY; }