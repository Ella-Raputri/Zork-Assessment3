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
#include "core/ZOOrkEngine.h"
#include "utils/Color.h"

int main() {
    auto outside = std::make_shared<Room>("outside", "The outside world.", 18, 3, 18, 3);
    auto inside  = std::make_shared<Room>("inside",  "Inside the house.",  4,  2,  4,  2);

    auto frontDoorState = std::make_shared<DoorState>(true);

    // Build outside grid
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 18; x++)
            outside->setCell(x, y, CellType::Floor, 'x', "You are in the garden.", "garden", true, Color::GREEN);

    for (int y = 1; y <= 2; y++)
        for (int x = 8; x <= 11; x++)
            outside->setCell(x, y, CellType::Floor, 'h', "You are inside the house.", "house", true, Color::WHITE);
    
    for (int y = 1; y <= 2; y++)
        for (int x = 14; x <= 16; x++)
            outside->setRestrictedCell(x, y, '~', "You are underwater.", "underwater", "diving_suit" , "Restricted area: need diving suit", Color::BLUE);

    outside->setDoorCell(11, 2, frontDoorState, "silver_key");
    // outside->setCell(14, 2, CellType::Impassable, 'w', "You are at the wall.", "wall", false, Color::CYAN);

    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 4; x++)
            inside->setCell(x, y, CellType::Floor, 'h', "You are inside.", "house", true, Color::WHITE);

    inside->setDoorCell(3, 1, frontDoorState, "silver_key");

    Passage::createBasicPassage(
        outside.get(), inside.get(),
        "west",
        11, 2,
        3, 1,
        12, 2,
        2, 1,
        true    
    );

    auto key = std::make_shared<UsableItem>(
        "key",
        "A small silver key lying on the floor.",
        "silver_key",
        std::make_shared<NullCommand>(),
        ItemType::Key,
        -1
    );
    outside->getCell(13, 2)->addItem(key);

    auto merchant = std::make_shared<NPC>(
        "merchant",
        "A suspicious trader.",
        std::vector<std::string>{
            "Welcome traveler.",
            "I sell useful things.",
            "Bring me a golden key."
        }
    );

    merchant->setPosition(1, 1);
    inside->addNPC(merchant);
    
    auto divingSuit = std::make_shared<EquippableItem>(
        "diving_suit",
        "A heavy diving suit with an oxygen tank.",
        "diving_suit",
        "underwater"
    );
    outside->getCell(13, 1)->addItem(divingSuit);

    auto mirrorShards = std::make_shared<ClueItem>(
        "mirror_shards",
        "Some remaining of a mirror.",
        "mirror_shards"
    );
    outside->getCell(0, 1)->addItem(mirrorShards);

    ZOOrkEngine zoork(outside, 12, 2);
    zoork.run();
    return 0;
}