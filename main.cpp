#include "command/RoomDefaultEnterCommand.h"
#include "location/passage/Passage.h"
#include "entity/Player.h"
#include "location/room/Room.h"
#include "core/ZOOrkEngine.h"

int main() {
    auto outside = std::make_shared<Room>("outside", "The outside world.", 18, 3, 18, 3);
    auto inside  = std::make_shared<Room>("inside",  "Inside the house.",  4,  2,  4,  2);

    // Build outside grid
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 18; x++)
            outside->setCell(x, y, CellType::Empty, 'x', "You are in the garden.", "garden", true);

    for (int y = 1; y <= 2; y++)
        for (int x = 8; x <= 11; x++)
            outside->setCell(x, y, CellType::Floor, 'h', "You are inside the house.", "house", true);

    outside->setCell(11, 2, CellType::Door, 'd', "You are at the door.", "door", true);

    // Build inside grid — now correctly 8x4
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 4; x++)
            inside->setCell(x, y, CellType::Floor, 'h', "You are inside.", "house", true);

    inside->setCell(3, 1, CellType::Door, 'd', "You are at the door.", "door", true);

    Passage::createBasicPassage(
        outside.get(), inside.get(),
        "west",
        11, 2,
        3, 1,
        12, 2,
        2, 1,
        true    
    );

    ZOOrkEngine zoork(outside, 12, 2);
    zoork.run();
    return 0;
}