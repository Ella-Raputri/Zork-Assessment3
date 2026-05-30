#ifndef ITEM_LOADER_H
#define ITEM_LOADER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

#include "../location/room/Room.h"
#include "../entity/item/Item.h"
#include "../entity/item/UsableItem.h"
#include "../entity/item/EquippableItem.h"
#include "../entity/item/ClueItem.h"
#include "../command/NullCommand.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;


class ItemLoader {
public:
    static std::unordered_map<std::string, std::shared_ptr<Item>>
    loadItems(
        const std::string& filepath,
        std::shared_ptr<Room> outside,
        std::unordered_map<std::string,
        std::shared_ptr<Room>>& interiors
    );
};

#endif