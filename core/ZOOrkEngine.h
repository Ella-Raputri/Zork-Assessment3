//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "../entity/character/Player.h"
#include "../location/Location.h"
#include "../location/passage/Passage.h"
#include "../location/cell/DoorCell.h"
#include "../entity/character/NPC.h"
#include "../entity/item/UsableItem.h"
#include "../entity/item/EquippableItem.h"
#include "../entity/item/ClueItem.h"
#include "../map/MapLoader.h"
#include "CheckpointManager.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

class ZOOrkEngine {
public:
    ZOOrkEngine(int startX, int startY);
    void run();

private:
    bool gameOver = false;
    Player *player;
    CheckpointManager* checkpointManager;
    
    std::shared_ptr<Room> world;
    std::unordered_map<std::string, std::shared_ptr<Room>> interiors;

    void handleGoCommand(std::vector<std::string>);
    void handleLookCommand();

    void handleTakeCommand(std::vector<std::string>);
    void handleDropCommand(std::vector<std::string>);
    void handleUseCommand(std::vector<std::string>);
    void handleTalkCommand(std::vector<std::string>);
    void handleInventoryCommand();

    void handleEquipCommand(std::vector<std::string>);
    void handleUnequipCommand();
    void handleHelpCommand();
    void handleMapCommand();
    void handleTeleportCommand(std::vector<std::string>);
    
    void handleQuitCommand();

    static std::string combineArguments(const std::vector<std::string>&);
    static std::vector<std::string> tokenizeString(const std::string&);
    static std::string makeLowercase(std::string);

    std::shared_ptr<DoorCell> getNearbyDoor();
    std::shared_ptr<Room> initMap();
};


#endif //ZOORK_ZOORKENGINE_H
