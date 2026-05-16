#include "command/RoomDefaultEnterCommand.h"
#include "location/passage/Passage.h"
#include "entity/Player.h"
#include "location/room/Room.h"
#include "core/ZOOrkEngine.h"


int main() {
    // std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
    //                        "You are standing in an open field west of a white house, with a boarded front door.\n");

    // std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
    //                                 "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    // std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
    //                               "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    // Passage::createBasicPassage(start.get(), south_of_house.get(), "south", true);
    // Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);

    auto world = std::make_shared<Room>("world", "The world.", 18, 3);
    for (int y = 1; y <= 2; y++)
        for (int x = 8; x <= 11; x++)
            world->setCell(x, y, CellType::Floor, 'h', "You are inside the house.", "house", true);

    world->setCell(11, 2, CellType::Door, 'd', "You are at the door.", "door", true);

    ZOOrkEngine zoork(world, 12, 2);

    zoork.run();

    return 0;
}
