#ifndef NPC_LOADER_H
#define NPC_LOADER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

#include "../entity/character/NPC.h"
#include "../location/room/Room.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;


class NPCLoader {
public:
    static std::unordered_map<std::string, std::shared_ptr<NPC>> loadNPCs(
        const std::string& filepath,
        std::shared_ptr<Room> outside,
        std::unordered_map<std::string, std::shared_ptr<Room>>& interiors
    );
};

#endif