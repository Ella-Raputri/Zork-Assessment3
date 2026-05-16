//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "../../entity/Character.h"
#include "../../command/RoomDefaultEnterCommand.h"
#include "../../entity/Item.h"
#include "../Location.h"
#include "../Cell.h"
#include <memory>
#include <map>
#include <vector>
#include <string>

class Passage;

class Room : public Location {
public:
    Room(const std::string &n, const std::string &d, int width, int height);

    // Room(const std::string &n, const std::string &d, std::shared_ptr<Command>);

//    void addItem(Item*);
//    void removeItem(const std::string&);
//    Item* getItem(const std::string&);
//    Item* retrieveItem(const std::string&);
//    void addCharacter(Character*);
//    void removeCharacter(const std::string&);
//    Character* getCharacter(const std::string&);
    Cell& getCell(int x, int y);
    void setCell (int x, int y, CellType type, char symbol, const std::string &description, const std::string &regionTag,
                 bool passable);
    
    std::string canMoveTo(int fromX, int fromY, int toX, int toY) const;
    void render(int playerX, int playerY) const;

    int getWidth() const;
    int getHeight() const;

    void addPassage(const std::string & direction, std::shared_ptr<Passage> p);
    void removePassage(const std::string & direction);
    std::shared_ptr<Passage> getPassage(const std::string & direction);

protected:
//    std::vector<Item*> items;
//    std::vector<Character*> characters;
    int width, height;
    std::vector<std::vector<Cell>> grid;  // grid[y][x]
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
};


#endif //ZOORK_ROOM_H
