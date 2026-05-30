#include "ItemLoader.h"

std::unordered_map<std::string, std::shared_ptr<Item>>
ItemLoader::loadItems(
    const std::string& filepath,
    std::shared_ptr<Room> outside,
    std::unordered_map<std::string, std::shared_ptr<Room>>& interiors
) {
    std::unordered_map<std::string, std::shared_ptr<Item>> registry;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Failed to open item file: " << filepath << "\n";
        return registry;
    }

    json root;
    try {
        file >> root;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return registry;
    }

    for (const auto& entry : root["items"]) {
        std::string id = entry["id"];
        std::string type = entry["type"];
        std::string name = entry["name"];
        std::string desc = entry["description"];

        std::shared_ptr<Item> item;

        if (type == "key" || type == "generic") {
            int uses = entry.value("use", -1);
            ItemType itemType = type == "key"? ItemType::Key : ItemType::Generic;
            item = std::make_shared<UsableItem>(
                name,
                desc,
                id,
                std::make_shared<NullCommand>(),
                itemType,
                uses
            );
        }
        else if (type == "clue") {
            item = std::make_shared<ClueItem>(
                name,
                desc,
                id
            );
        }
        else if (type == "equippable") {
            std::string region = entry.value("requiredRegion", "");
            item = std::make_shared<EquippableItem>(
                name,
                desc,
                id,
                region
            );
        }

        if (!item) continue;

        registry[id] = item;
        bool spawn = entry.value("spawn", false);

        if (!spawn) continue;
        std::string roomName = entry.value("room", "outside");

        int x = entry["x"];
        int y = entry["y"];

        std::shared_ptr<Room> targetRoom;

        if (roomName == "outside") {
            targetRoom = outside;
        }
        else {
            auto it = interiors.find(roomName);
            if (it == interiors.end()) {
                std::cerr << "Unknown room: " << roomName << "\n";
                continue;
            }
            targetRoom = it->second;
        }

        targetRoom->getCell(x, y)->addItem(item);
    }

    return registry;
}