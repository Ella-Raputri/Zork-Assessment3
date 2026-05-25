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
    grid.resize(height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y].push_back(std::make_shared<Cell>());
        }
    }
}


void Room::addNPC(std::shared_ptr<NPC> npc){
    npcs.push_back(npc);
}

std::shared_ptr<NPC> Room::getNPC(const std::string& name){
    for (auto& npc: npcs){
        if(npc->getName() == name) return npc;
    }
    return nullptr;
}

std::shared_ptr<NPC> Room::getNPCAt(int x, int y) const{
    for (auto& npc: npcs){
        if(npc->getX() == x && npc->getY() == y) return npc;
    }
    return nullptr;
}

bool Room::hasNPCAt(int x, int y) const {
    for (const auto& npc : npcs) {
        if (npc->getX() == x && npc->getY() == y) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Cell> Room::getCell(int x, int y){
    return grid[y][x];
}

void Room::setCell(int x, int y, CellType type, char symbol,
                   const std::string &description, const std::string &regionTag,
                   bool passable, const std::string &color) {
    grid[y][x]->setType(type);
    grid[y][x]->setSymbol(symbol);
    grid[y][x]->setDescription(description);
    grid[y][x]->setRegionTag(regionTag);
    grid[y][x]->setPassable(passable);
    grid[y][x]->setColor(color);
}

void Room::setDoorCell(int x, int y, std::shared_ptr<DoorState> state, const std::string& keyId){
    grid[y][x] = std::make_shared<DoorCell>(state, keyId);
}

std::string Room::canMoveTo(int fromX, int fromY, int toX, int toY, const std::string &direction) const {
    if(toX < 0 || toX >= width || toY < 0 || toY >= height){
        return "It is impossible to go " + direction + "!";
    }

    if (hasNPCAt(toX, toY)) {
        return "Someone is blocking your way.";
    }

    auto from = grid[fromY][fromX];
    auto to = grid[toY][toX];

    if(!to->isPassable()){ 
        if(to->getType() == CellType::Door) return "Door is locked.";
        return "Something is blocking your way.";
    };

    if (from->getRegionTag() != to->getRegionTag()) {
        if (to->getType() != CellType::Door && from->getType() != CellType::Door){
            return "You can't go directly from the " + from->getRegionTag() +
                   " to the " + to->getRegionTag() + ". You'll need to find a door.";
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
                auto cell = grid[y][x];

                auto npc = getNPCAt(x, y);
                if (npc) {
                    std::cout << Color::YELLOW << 'N' << Color::RESET;
                }
                else if (cell->hasItems()) {
                    std::cout << Color::YELLOW << '!' << Color::RESET;
                }else{
                    std::cout << cell->getColor() << cell->getSymbol() << Color::RESET;
                }                
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