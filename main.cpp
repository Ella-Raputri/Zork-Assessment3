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

    ZOOrkEngine zoork(outside, 20, 16);

    zoork.run();
    return 0;
}