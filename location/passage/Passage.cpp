//
// Created by Richard Skarbez on 5/7/23.
//

#include "Passage.h"

#include <utility>
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
                                   int fromX, int fromY,   
                                   int toX,   int toY,     
                                   bool bidirectional) {

    std::string passageName = from->getName() + "_to_" + to->getName();
    auto temp1 = std::make_shared<Passage>(passageName, "A totally normal passageway.", from, to, fromX, fromY, toX, toY);
    from->addPassage(direction, temp1);
    
    if (bidirectional) {
        std::string passageName2 = to->getName() + "_to_" + from->getName();
        auto temp2 = std::make_shared<Passage>(passageName2, "A totally normal passageway.", to, from, toX, toY, fromX, fromY);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

Passage::Passage(const std::string &n, const std::string &d,
            Room* from, Room* to,
            int fromX, int fromY,
            int toX,   int toY)
        : Location(n, d), fromRoom(from), toRoom(to),
        fromX(fromX), fromY(fromY), toX(toX), toY(toY) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

// Passage::Passage(const std::string &n, const std::string &d, std::shared_ptr<Command> c, Room* from,
//                  Room* to)
//         : Location(n, d, std::move(c)), fromRoom(from), toRoom(to) {}

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

int Passage::getFromX() const {
    return fromX;
}

int Passage::getFromY() const {
    return fromY;
}

int Passage::getToX() const {
    return toX;
}

int Passage::getToY() const {
    return toY;
}