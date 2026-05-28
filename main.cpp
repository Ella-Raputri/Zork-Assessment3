#include "command/RoomDefaultEnterCommand.h"
#include "location/passage/Passage.h"
#include "entity/character/Player.h"
#include "entity/character/NPC.h"
#include "entity/item/Item.h"
#include "entity/item/UsableItem.h"
#include "entity/item/EquippableItem.h"
#include "entity/item/ClueItem.h"
#include "command/NullCommand.h"
#include "location/room/Room.h"
#include "map/MapLoader.h"
#include "core/ZOOrkEngine.h"
#include "utils/Color.h"

int main() {
    auto outside = std::make_shared<Room>(
        "Estate", "The estate grounds.",
        43, 23, 43, 23
    );

    auto regions = MapLoader::loadRegions("data/map.csv");
    MapLoader::applyRegions(outside, regions);
    auto interiors = MapLoader::createSeparateRooms(regions);

    MapLoader::connectSeparateRooms(
        outside,
        regions,
        interiors
    );

    auto key = std::make_shared<UsableItem>(
        "silver_key",
        "A small silver key lying on the floor.",
        "silver_key",
        std::make_shared<NullCommand>(),
        ItemType::Key,
        -1
    );
    outside->getCell(20, 17)->addItem(key);

    auto master_key = std::make_shared<UsableItem>(
        "master_key",
        "A master key.",
        "master_key",
        std::make_shared<NullCommand>(),
        ItemType::Key,
        -1
    );
    outside->getCell(25, 16)->addItem(master_key);

    auto divingSuit = std::make_shared<EquippableItem>(
        "diving_suit",
        "A heavy diving suit with an oxygen tank.",
        "diving_suit",
        "Lily Pond"
    );
    outside->getCell(14, 14)->addItem(divingSuit);

    auto mirrorShards = std::make_shared<ClueItem>(
        "mirror_shards",
        "Some remaining of a mirror.",
        "mirror_shards"
    );
    outside->getCell(13, 12)->addItem(mirrorShards);

    ZOOrkEngine zoork(outside, 26, 16);

    zoork.run();
    return 0;
}