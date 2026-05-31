// CheckpointManager.h
#ifndef ZOORK_CHECKPOINTMANAGER_H
#define ZOORK_CHECKPOINTMANAGER_H

#include "../location/room/Room.h"
#include "../entity/character/NPC.h"
#include "../entity/item/Item.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct CheckpointData {
    std::string id;
    bool triggered = false;

    std::vector<std::string> requiredClueIds; 
    std::string requiredNPCName;
    int triggerX, triggerY;

    std::vector<std::function<bool()>> onTrigger;
    std::string requiredCheckpointId = "";
};

enum class CheckpointResult {
    NotMatched,
    Success,
    Failed
};

class CheckpointManager {
public:
    static CheckpointManager* instance();

    void loadFromJSON(const std::string& filepath, std::shared_ptr<Room> outside,
                      std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
                      std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
                      std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry);

    CheckpointResult tryTrigger(const std::string& npcName, int x, int y, Player* player);

private:
    CheckpointManager() = default;
    static CheckpointManager* _instance;
    std::vector<CheckpointData> checkpoints;

    std::function<bool()> buildEffect(
        const json& effect,
        std::shared_ptr<Room> outside,
        std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
        std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
        std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry
    );
};

#endif