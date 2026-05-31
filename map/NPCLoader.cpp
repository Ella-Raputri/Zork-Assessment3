#include "NPCLoader.h"

std::unordered_map<std::string, std::shared_ptr<NPC>> NPCLoader::loadNPCs(
    const std::string& filepath,
    std::shared_ptr<Room> outside,
    std::unordered_map<std::string, std::shared_ptr<Room>>& interiors
) {
    std::unordered_map<std::string, std::shared_ptr<NPC>> registry;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Failed to open npc file: " << filepath << "\n";
        return registry;
    }

    json root;
    try {
        file >> root;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return registry;
    }

    for (const auto& entry : root["npcs"]) {
        std::string name = entry["name"];
        std::string desc = entry["description"];

        std::vector<std::vector<std::string>> dialogueStages;

        for (const auto& stage : entry["dialogueStages"]) {
            std::vector<std::string> lines;
            for (const auto& line : stage) {
                lines.push_back(
                    line.get<std::string>()
                );
            }
            dialogueStages.push_back(lines);
        }

        auto npc = std::make_shared<NPC>(
            name,
            desc,
            dialogueStages
        );

        int x = entry["x"];
        int y = entry["y"];
        npc->setPosition(x, y);

        std::string roomName =  entry.value("room", "outside");
        std::shared_ptr<Room> targetRoom;

        if (roomName == "outside") {
            targetRoom = outside;
        }
        else {
            auto roomIt = interiors.find(roomName);
            if (roomIt == interiors.end()) {
                std::cerr << "Unknown room: " << roomName << "\n";
                continue;
            }
            targetRoom = roomIt->second;
        }

        targetRoom->addNPC(npc);
        registry[name] = npc;
    }

    return registry;
}