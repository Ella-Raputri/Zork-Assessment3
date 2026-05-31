// CheckpointManager.cpp
#include "CheckpointManager.h"
#include <fstream>
#include <iostream>

CheckpointManager* CheckpointManager::_instance = nullptr;

CheckpointManager* CheckpointManager::instance() {
    if (!_instance) _instance = new CheckpointManager();
    return _instance;
}

void CheckpointManager::registerCheckpoint(CheckpointData cp) {
    checkpoints.push_back(std::move(cp));
}

bool CheckpointManager::tryTrigger(const std::string& npcName, int x, int y, Player* player) {
    for (auto& cp : checkpoints) {
        if (cp.triggered){
            continue;
        } 
        if (cp.requiredNPCName != npcName){
            continue;
        } 
        if (cp.triggerX != x || cp.triggerY != y){
            continue;
        } 

        bool hasAllClues = true;
        for (const auto& clueId : cp.requiredClueIds) {
            if (!player->getItemById(clueId)) {
                hasAllClues = false;
                std::cout << "[You feel like you're missing something...]\n";
                break;
            }
        }
        if (!hasAllClues){
            continue;
        }

        cp.triggered = true;
        std::cout << "[Checkpoint reached: " << cp.id << "]\n";
        for (auto& effect : cp.onTrigger) effect();
        return true;
    }
    return false;
}

bool CheckpointManager::isTriggered(const std::string& id) const {
    for (const auto& cp : checkpoints) {
        if (cp.id == id) return cp.triggered;
    }
    return false;
}

std::unordered_map<std::string, bool> CheckpointManager::getFlags() const {
    std::unordered_map<std::string, bool> flags;
    for (const auto& cp : checkpoints) {
        flags[cp.id] = cp.triggered;
    }
    return flags;
}

void CheckpointManager::loadFlags(const std::unordered_map<std::string, bool>& flags) {
    for (auto& cp : checkpoints) {
        auto it = flags.find(cp.id);
        if (it != flags.end() && it->second) {
            cp.triggered = true;
            // Re-apply effects so world state matches saved state
            for (auto& effect : cp.onTrigger) effect();
        }
    }
}

// -------------------------------------------------------

std::function<void()> CheckpointManager::buildEffect(
    const json& effect,
    std::shared_ptr<Room> outside,
    std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
    std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
    std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry
) {
    std::string type = effect["type"];

    if (type == "move_npc") {
        std::string npcName = effect["npc"];
        int x = effect["x"], y = effect["y"];

        auto npcIt = npcRegistry.find(npcName);
        if (npcIt == npcRegistry.end()) return [](){};
        auto npc = npcIt->second;

        return [npc, x, y, npcName]() {
            npc->setPosition(x, y);
            std::cout << npcName << " has moved.\n";
        };
    }

    if (type == "set_dialogue_stage") {
        std::string npcName = effect["npc"];
        int stage = effect["stage"];

        auto npcIt = npcRegistry.find(npcName);
        if (npcIt == npcRegistry.end()) return [](){};
        auto npc = npcIt->second;

        return [npc, stage]() {
            npc->setDialogueStage(stage);
        };
    }

    if (type == "spawn_item") {
        std::string itemId  = effect["itemId"];
        std::string roomName = effect.value("room", "outside");
        int x = effect["x"], y = effect["y"];

        auto itemIt = itemRegistry.find(itemId);
        if (itemIt == itemRegistry.end()) {
            std::cerr << "spawn_item: unknown item " << itemId << "\n";
            return [](){};
        }
        auto item = itemIt->second;

        std::shared_ptr<Room> targetRoom;
        if (roomName == "outside") {
            targetRoom = outside;  
        } else {
            auto roomIt = interiors.find(roomName);
            if (roomIt == interiors.end()) {
                std::cerr << "spawn_item: unknown room " << roomName << "\n";
                return [](){};
            }
            targetRoom = roomIt->second;
        }

        return [item, targetRoom, itemId, x, y]() {
            auto cell = targetRoom->getCell(x, y);
            if (!cell->getItemById(itemId)) {
                cell->addItem(item);
                std::cout << "A new item: " << item->getName() << " has spawned.\n";
            }
        };
    }

    if (type == "print_message") {
        std::string message = effect["message"];
        return [message]() {
            std::cout << "[Story] " << message << "\n";
        };
    }

    std::cerr << "Unknown effect type: " << type << "\n";
    return [](){};
}

// -------------------------------------------------------

void CheckpointManager::loadFromJSON(
    const std::string& filepath,
    std::shared_ptr<Room> outside,
    std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
    std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
    std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry
) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open checkpoint file: " << filepath << "\n";
        return;
    }

    json root;
    try {
        file >> root;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return;
    }

    if (!root.contains("checkpoints")) {
        std::cerr << "JSON has no 'checkpoints' key\n";
        return;
    }

    std::cout << "JSON parsed OK, found " << root["checkpoints"].size() << " entries\n";

    for (const auto& entry : root["checkpoints"]) {
        CheckpointData cp;
        cp.id = entry["id"];
        cp.triggered = false;

        // Multiple required clues
        for (const auto& clueId : entry["requiredClueIds"]) {
            cp.requiredClueIds.push_back(clueId.get<std::string>());
        }

        cp.requiredNPCName = entry["requiredNPCName"];
        cp.triggerX = entry["triggerX"];
        cp.triggerY = entry["triggerY"];

        // Build effect lambdas from JSON
        for (const auto& effect : entry["effects"]) {
            cp.onTrigger.push_back(
                buildEffect(effect, outside, interiors, npcRegistry, itemRegistry)
            );
        }

        checkpoints.push_back(std::move(cp));
    }

    std::cout << "Loaded " << checkpoints.size() << " checkpoints.\n";
}