#include "command/RoomDefaultEnterCommand.h"
#include "location/passage/Passage.h"
#include "entity/Player.h"
#include "entity/Item.h"
#include "command/NullCommand.h"
#include "location/room/Room.h"
#include "core/ZOOrkEngine.h"
#include "utils/Color.h"

int main() {
    auto outside = std::make_shared<Room>("outside", "The outside world.", 18, 3, 18, 3);
    auto inside  = std::make_shared<Room>("inside",  "Inside the house.",  4,  2,  4,  2);

    // Build outside grid
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 18; x++)
            outside->setCell(x, y, CellType::Empty, 'x', "You are in the garden.", "garden", true, Color::GREEN);

    for (int y = 1; y <= 2; y++)
        for (int x = 8; x <= 11; x++)
            outside->setCell(x, y, CellType::Floor, 'h', "You are inside the house.", "house", true, Color::WHITE);

    outside->setCell(11, 2, CellType::Door, 'd', "You are at the door.", "door", true, Color::RED);
    outside->setCell(14, 2, CellType::Impassable, 'w', "You are at the wall.", "wall", false, Color::CYAN);

    // Build inside grid — now correctly 8x4
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 4; x++)
            inside->setCell(x, y, CellType::Floor, 'h', "You are inside.", "house", true, Color::WHITE);

    inside->setCell(3, 1, CellType::Door, 'd', "You are at the door.", "door", true, Color::RED);

    Passage::createBasicPassage(
        outside.get(), inside.get(),
        "west",
        11, 2,
        3, 1,
        12, 2,
        2, 1,
        true    
    );

    auto key = std::make_shared<Item>(
        "key",
        "A small silver key lying on the floor.",
        std::make_shared<NullCommand>(),
        2,
        ItemType::Key
    );
    inside->getCell(2, 0).addItem(key);

    ZOOrkEngine zoork(outside, 12, 2);
    zoork.run();
    return 0;
}