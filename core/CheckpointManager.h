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

    std::vector<std::function<void()>> onTrigger;
};


class CheckpointManager {
public:
    static CheckpointManager* instance();

    void loadFromJSON(const std::string& filepath, std::shared_ptr<Room> outside,
                      std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
                      std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
                      std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry);

    void registerCheckpoint(CheckpointData cp);
    bool tryTrigger(const std::string& npcName, int x, int y, Player* player);
    bool isTriggered(const std::string& id) const;

    // For save/load
    std::unordered_map<std::string, bool> getFlags() const;
    void loadFlags(const std::unordered_map<std::string, bool>& flags);

private:
    CheckpointManager() = default;
    static CheckpointManager* _instance;
    std::vector<CheckpointData> checkpoints;

    std::function<void()> buildEffect(
        const json& effect,
        std::shared_ptr<Room> outside,
        std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
        std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
        std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry
    );
};

#endif