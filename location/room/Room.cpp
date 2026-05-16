//
// Created by Richard Skarbez on 5/7/23.
//
#include "Room.h"
#include "../passage/NullPassage.h"

#include <utility>
#include <memory>
#include <iostream>


Room::Room(const std::string &n, const std::string &d, int width, int height)
        : Location(n, d), width(width), height(height) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
    grid.resize(height, std::vector<Cell>(width));
}

Cell& Room::getCell(int x, int y){
    return grid[y][x];
}

void Room::setCell(int x, int y, CellType type, char symbol,
                   const std::string &description, const std::string &regionTag,
                   bool passable) {
    grid[y][x].setType(type);
    grid[y][x].setSymbol(symbol);
    grid[y][x].setDescription(description);
    grid[y][x].setRegionTag(regionTag);
    grid[y][x].setPassable(passable);
}

std::string Room::canMoveTo(int fromX, int fromY, int toX, int toY) const {
    if(toX < 0 || toX >= width || toY < 0 || toY >= height){
        return "There's nothing there.";
    }
    const Cell& from = grid[fromY][fromX];
    const Cell& to = grid[toY][toX];

    if(!to.isPassable()) return "Something is blocking your way.";

    if (from.getRegionTag() != to.getRegionTag()) {
        if (to.getType() != CellType::Door && from.getType() != CellType::Door){
            return "You can't go directly from the " + from.getRegionTag() +
                   " to the " + to.getRegionTag() + ". You'll need to find a door.";
        }  
    }

    return "";
};

void Room::render(int playerX, int playerY) const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == playerX && y == playerY)
                std::cout << '@';
            else
                std::cout << grid[y][x].getSymbol();
        }
        std::cout << '\n';
    }
}

int Room::getWidth() const { 
    return width; 
}
int Room::getHeight() const { 
    return height; 
}

// Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}