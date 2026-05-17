//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//
#include "Room.h"
#include "../passage/NullPassage.h"

#include <utility>
#include <memory>
#include <iostream>
#include <algorithm>


Room::Room(const std::string &n, const std::string &d, int width, int height, int viewW, int viewH)
        : Location(n, d), width(width), height(height), viewW(viewW), viewH(viewH) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
    grid.resize(height, std::vector<Cell>(width));
}

Cell& Room::getCell(int x, int y){
    return grid[y][x];
}

void Room::setCell(int x, int y, CellType type, char symbol,
                   const std::string &description, const std::string &regionTag,
                   bool passable, const std::string &color) {
    grid[y][x].setType(type);
    grid[y][x].setSymbol(symbol);
    grid[y][x].setDescription(description);
    grid[y][x].setRegionTag(regionTag);
    grid[y][x].setPassable(passable);
    grid[y][x].setColor(color);
}

std::string Room::canMoveTo(int fromX, int fromY, int toX, int toY, const std::string &direction) const {
    if(toX < 0 || toX >= width || toY < 0 || toY >= height){
        return "It is impossible to go " + direction + "!";
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

void Room::render(int playerX, int playerY, int viewW, int viewH) const {
    int startX = std::clamp(playerX - viewW / 2, 0, std::max(0, width - viewW));
    int startY = std::clamp(playerY - viewH / 2, 0, std::max(0, height - viewH));

    for (int y = startY; y < startY + viewH; y++) {
        for (int x = startX; x < startX + viewW; x++) {
            if (x == playerX && y == playerY){
                std::cout << '@';
            }
            else if (x < width && y < height){
                const Cell& cell = grid[y][x];
                std::cout << cell.getColor() << cell.getSymbol() << Color::RESET;
            }
            else{
                std::cout << ' ';
            }
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
int Room::getViewW() const { 
    return viewW; 
}
int Room::getViewH() const { 
    return viewH; 
}

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
        return std::make_shared<NullPassage>(this);
    }
}

std::shared_ptr<Passage> Room::getPassageByPosition(int x, int y) {
    for (auto& [dir, passage] : passageMap) {
        if (passage->getDoorX() == x && passage->getDoorY() == y)
            return passage;
    }
    return std::make_shared<NullPassage>(this);
}

void Room::addItem(std::shared_ptr<Item> item){
    items.push_back(item);
}

void Room::removeItem(const std::string& itemName){
    for(auto it = items.begin(); it != items.end(); it++){
        if ((*it)->getName() == itemName) {
            items.erase(it);
            return;
        }
    }
    std::cout << "No " << itemName << " found in this room." << std::endl;
}

std::shared_ptr<Item> Room::getItem(const std::string& itemName){
    for (auto &item : items) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

std::shared_ptr<Item> Room::retrieveItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); it++) {
        if ((*it)->getName() == itemName) {
            auto item = *it;
            items.erase(it);
            return item;
        }
    }
    return nullptr;
}