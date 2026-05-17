//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "../../entity/Character.h"
#include "../../command/RoomDefaultEnterCommand.h"
#include "../../entity/Item.h"
#include "../Location.h"
#include "../cell/Cell.h"
#include "../cell/DoorCell.h"
#include "../../utils/Color.h"
#include <memory>
#include <map>
#include <vector>
#include <string>

class Passage;

class Room : public Location {
public:
    Room(const std::string &n, const std::string &d, int width, int height, int viewW, int viewH);

//    void addCharacter(Character*);
//    void removeCharacter(const std::string&);
//    Character* getCharacter(const std::string&);
    std::shared_ptr<Cell> getCell(int x, int y);
    void setCell (int x, int y, CellType type, char symbol, const std::string &description, const std::string &regionTag,
                 bool passable, const std::string &color);
    void setDoorCell(int x, int y, std::shared_ptr<DoorState> state, const std::string& keyId);
    
    std::string canMoveTo(int fromX, int fromY, int toX, int toY, const std::string &direction) const;
    void render(int playerX, int playerY, int viewW, int viewH) const;

    int getWidth() const;
    int getHeight() const;
    int getViewW() const;
    int getViewH() const;

    void addPassage(const std::string & direction, std::shared_ptr<Passage> p);
    void removePassage(const std::string & direction);
    std::shared_ptr<Passage> getPassage(const std::string & direction);
    std::shared_ptr<Passage> getPassageByPosition(int x, int y);

protected:
//    std::vector<Character*> characters;
    int width, height;
    int viewW, viewH;
    std::vector<std::vector<std::shared_ptr<Cell>>> grid;  // grid[y][x]
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
};


#endif //ZOORK_ROOM_H
