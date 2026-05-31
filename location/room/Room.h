//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "../../entity/character/NPC.h"
#include "../../entity/character/Player.h"
#include "../../command/RoomDefaultEnterCommand.h"
#include "../../entity/item/Item.h"
#include "../Location.h"
#include "../cell/Cell.h"
#include "../cell/DoorCell.h"
#include "../cell/RestrictedCell.h"
#include "../../utils/Color.h"
#include <memory>
#include <map>
#include <vector>
#include <string>

class Passage;

class Room : public Location {
public:
    Room(const std::string &n, const std::string &d, int width, int height, int viewW, int viewH);

    void addNPC(std::shared_ptr<NPC> npc);
    void removeNPC(const std::string& name);
    std::shared_ptr<NPC> getNPC(const std::string& name);
    std::shared_ptr<NPC> getNPCAt(int x, int y) const;
    bool hasNPCAt(int x, int y) const;

    std::shared_ptr<Cell> getCell(int x, int y);
    void setCell (int x, int y, CellType type, char symbol, const std::string &description, const std::string &regionTag,
                 bool passable, const std::string &color);
    void setDoorCell(int x, int y, std::shared_ptr<DoorState> state, const std::string& keyId);
    
    void setRestrictedCell(
        int x,
        int y,
        char symbol,
        const std::string& description,
        const std::string& regionTag,
        const std::string& requiredItemId,
        const std::string& failMessage,
        const std::string& color
    );

    std::string canMoveTo(int fromX, int fromY, int toX, int toY, const std::string &direction, Player* player) const;
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
    std::vector<std::shared_ptr<NPC>> npcs;
    int width, height;
    int viewW, viewH;
    std::vector<std::vector<std::shared_ptr<Cell>>> grid;  // grid[y][x]
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
};


#endif //ZOORK_ROOM_H
