#include "CheckpointManager.h"
#include <fstream>
#include <iostream>

CheckpointManager* CheckpointManager::_instance = nullptr;

CheckpointManager* CheckpointManager::instance() {
    if (!_instance) _instance = new CheckpointManager();
    return _instance;
}

CheckpointResult CheckpointManager::tryTrigger(const std::string& npcName, int x, int y, Player* player) {
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
        if (!cp.requiredCheckpointId.empty()) {
            bool prereqMet = false;
            for (const auto& other : checkpoints) {
                if (other.id == cp.requiredCheckpointId && other.triggered) {
                    prereqMet = true;
                    break;
                }
            }
            if (!prereqMet) continue;
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

        for (auto& effect : cp.onTrigger) {
            if (!effect()) return CheckpointResult::Failed;
        }
        cp.triggered = true;
        std::cout << "[Checkpoint reached: " << cp.id << "]\n";
        return CheckpointResult::Success;
    }
    return CheckpointResult::NotMatched;
}

std::function<bool()> CheckpointManager::buildEffect(
    const json& effect,
    std::shared_ptr<Room> outside,
    std::unordered_map<std::string, std::shared_ptr<Room>>& interiors,
    std::unordered_map<std::string, std::shared_ptr<NPC>>& npcRegistry,
    std::unordered_map<std::string, std::shared_ptr<Item>>& itemRegistry
) {
    std::string type = effect["type"];

    if (type == "ask_password") {
        std::string question = effect["question"];
        std::string answer = effect["answer"];

        return [question, answer]() -> bool {
            std::cout << question << "\n> ";

            std::string input;
            std::getline(std::cin, input);

            if (input == answer) {
                std::cout << "Correct.\n";
                return true;
            }

            std::cout << "Wrong password.\n";
            return false;
        };
    }

    if (type == "move_npc") {
        std::string npcName = effect["npc"];
        int x = effect["x"], y = effect["y"];
        std::string targetRoomName = effect.value("room", "");

        auto npcIt = npcRegistry.find(npcName);
        if (npcIt == npcRegistry.end()) []() -> bool { return false; };
        auto npc = npcIt->second;

        std::shared_ptr<Room> targetRoom = nullptr;
        if (!targetRoomName.empty()) {
            if (targetRoomName == "outside") {
                targetRoom = outside;
            } else {
                auto roomIt = interiors.find(targetRoomName);
                if (roomIt != interiors.end()) {
                    targetRoom = roomIt->second;
                } else {
                    std::cerr << "move_npc: unknown room " << targetRoomName << "\n";
                }
            }
        }

        return [npc, x, y, npcName, targetRoom]() -> bool {
            if (targetRoom) {
                Room* current = npc->getCurrentRoom();
                if (current && current != targetRoom.get()) {
                    current->removeNPC(npcName);
                    targetRoom->addNPC(npc);
                    npc->setCurrentRoom(targetRoom.get());
                }
            }
            npc->setPosition(x, y);
            std::cout << npcName << " has moved.\n";
            return true;
        };
    }

    if (type == "set_dialogue_stage") {
        std::string npcName = effect["npc"];
        int stage = effect["stage"];

        auto npcIt = npcRegistry.find(npcName);
        if (npcIt == npcRegistry.end()) []() -> bool { return false; };
        auto npc = npcIt->second;

        return [npc, stage]() -> bool {
            npc->setDialogueStage(stage);
            return true;
        };
    }

    if (type == "spawn_item") {
        std::string itemId  = effect["itemId"];
        std::string roomName = effect.value("room", "outside");
        int x = effect["x"], y = effect["y"];

        auto itemIt = itemRegistry.find(itemId);
        if (itemIt == itemRegistry.end()) {
            std::cerr << "spawn_item: unknown item " << itemId << "\n";
            return []() -> bool { return false; };
        }
        auto item = itemIt->second;

        std::shared_ptr<Room> targetRoom;
        if (roomName == "outside") {
            targetRoom = outside;  
        } else {
            auto roomIt = interiors.find(roomName);
            if (roomIt == interiors.end()) {
                std::cerr << "spawn_item: unknown room " << roomName << "\n";
                return []() -> bool { return false; };
            }
            targetRoom = roomIt->second;
        }

        return [item, targetRoom, itemId, x, y]() -> bool {
            auto cell = targetRoom->getCell(x, y);
            if (!cell->getItemById(itemId)) {
                cell->addItem(item);
                std::cout << "A new item: " << item->getName() << " has spawned.\n";
            }
            return true;
        };
    }

    if (type == "print_message") {
        std::string message = effect["message"];
        return [message]() -> bool {
            std::cout << "[Story] " << message << "\n";
            return true;
        };
    }

    std::cerr << "Unknown effect type: " << type << "\n";
    return []() -> bool { return false; };
}

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

        for (const auto& clueId : entry["requiredClueIds"]) {
            cp.requiredClueIds.push_back(clueId.get<std::string>());
        }

        cp.requiredNPCName = entry["requiredNPCName"];
        cp.triggerX = entry["triggerX"];
        cp.triggerY = entry["triggerY"];

        for (const auto& effect : entry["effects"]) {
            cp.onTrigger.push_back(
                buildEffect(effect, outside, interiors, npcRegistry, itemRegistry)
            );
        }
        cp.requiredCheckpointId = entry.value("requiredCheckpointId", "");
        checkpoints.push_back(std::move(cp));
    }

    std::cout << "Loaded " << checkpoints.size() << " checkpoints.\n";
}