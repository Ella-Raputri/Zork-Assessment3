//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#include "ZOOrkEngine.h"

#include <utility>
#include <algorithm>
#include <iostream>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start, int startX, int startY) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->setPosition(startX, startY);
    player->getCurrentRoom()->render(startX, startY, player->getCurrentRoom()->getViewW(), player->getCurrentRoom()->getViewH());
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "\n> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "use") {
            handleUseCommand(arguments);
        } else if (command == "talk" || command == "speak") {
            handleTalkCommand(arguments);
        } else if (command == "inventory") {
            handleInventoryCommand();
        } else if (command == "equip") {
            handleEquipCommand(arguments);
        } else if (command == "unequip") {
            handleUnequipCommand();
        } else if (command == "help") {
            handleHelpCommand();
        } else if (command == "map") {
            handleMapCommand();
        } else if (command == "teleport") {
            handleTeleportCommand(arguments);
        } else if (command == "quit" || command == "q") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    if(arguments.empty()){
        std::cout << "Please specify a direction!" << std::endl;
        return;
    }
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } 
    else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } 
    else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } 
    else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    // } else if (arguments[0] == "u" || arguments[0] == "up") {
    //     direction = "up";
    // } else if (arguments[0] == "d" || arguments[0] == "down") {
    //     direction = "down";
    } else {
        direction = arguments[0];
    }

    int dx = 0, dy = 0;
    if (direction == "north") dy = -1;
    else if (direction == "south") dy = +1;
    else if (direction == "east")  dx = +1;
    else if (direction == "west")  dx = -1;

    Room* currentRoom = player->getCurrentRoom();
    int currX = player->getX(), currY = player->getY();
    int newX = currX + dx, newY = currY + dy;

    std::string reason = currentRoom->canMoveTo(currX, currY, newX, newY, direction, player);

    if (!reason.empty()) {
        std::cout << reason << std::endl;
        return;
    }

    if (currentRoom->getCell(newX, newY)->getType() == CellType::Door) {
        auto passage = currentRoom->getPassage(direction);
        if (passage->getName() == "null") {
            passage = currentRoom->getPassageByPosition(newX, newY);
        }
        if (passage->getName() != "null") {
            passage->enter();
            player->setCurrentRoom(passage->getTo());
            player->setPosition(passage->getArriveX(), passage->getArriveY());
        }
    } else {
        player->setPosition(newX, newY);
        std::cout << currentRoom->getCell(newX, newY)->getDescription() << "\n";
    }

    handleMapCommand();
    player->checkEquippedRegion();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    std::cout << player->getCurrentRoom()->getDescription() << std::endl;

    Room* currentRoom = player->getCurrentRoom();
    int currX = player->getX();
    int currY = player->getY();
    auto cell = currentRoom->getCell(currX, currY);

    if (cell->hasItems()) {
        std::cout << "You see: " << std::endl;
        for (const auto& item : cell->getItems()) {
            std::cout << "- " << item->getName()
                      << ": " << item->getDescription() << std::endl;
        }
    }

    const std::vector<std::shared_ptr<NPC>> npcList = currentRoom->getNPCList();
    if(!npcList.empty()){
        std::cout << "In this room, you see: " << std::endl;
        for (const auto& npc : npcList) {
            std::cout << "- " << npc->getName()
                      << ": " << npc->getDescription() << std::endl;
        }
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if(arguments.empty()){
        std::cout << "Please specify what do you want to take." << std::endl;
        return;
    }
    Room* currentRoom = player->getCurrentRoom();
    int currX = player->getX(), currY = player->getY();

    auto cell = currentRoom->getCell(currX, currY);
    auto item = cell->retrieveItem(arguments[0]);

    if (item) {
        player->addItem(item);
        std::cout << "Taken: " << item->getName() << "\n";
    }
    else {
        std::cout << "No such item.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if(arguments.empty()){
        std::cout << "Please specify what do you want to drop." << std::endl;
        return;
    }
    Room* currentRoom = player->getCurrentRoom();
    int currX = player->getX(), currY = player->getY();

    auto cell = currentRoom->getCell(currX, currY);
    auto item = player->getItem(arguments[0]);

    if (item) {
        cell->addItem(item);
        std::cout << "Dropped: " << item->getName() << "\n";
    }
    else {
        std::cout << "No such item in the inventory.\n";
    }
}

void ZOOrkEngine::handleInventoryCommand() {
    player->showInventory();
}

void ZOOrkEngine::handleUseCommand(std::vector<std::string> arguments) {
    if(arguments.empty()){
        std::cout << "Please specify what do you want to use." << std::endl;
        return;
    }

    auto item = player->getItem(arguments[0]);
    if (!item) {
        std::cout << "No " << arguments[0] << " found in the inventory." << std::endl;
        return;        
    }

    auto usable = std::dynamic_pointer_cast<UsableItem>(item);
    if (!usable) {
        std::cout << "You cannot use this item. You can only equip it.\n";
        return;
    }

    if (usable->getType() == ItemType::Key) {
        auto door = getNearbyDoor();
        if (!door) {
            std::cout << "There is no door nearby." << std::endl;
            return;
        }

        if (door->canUnlockWith(usable->getItemId())){
            if(!door->isLocked()){
                door->lock();
                std::cout << "You locked the door." << std::endl;
            }else{
                door->unlock();
                std::cout << "You unlocked the door." << std::endl;
            }
        }else{
            std::cout << "The key does not fit." << std::endl;
        }
    }

    usable->use();
    if (usable->isDepleted()) {
        player->removeItem(arguments[0]);
        std::cout << "The " << usable->getName() << " is depleted and can not be used anymore." << std::endl;
    }
}

void ZOOrkEngine::handleTalkCommand(std::vector<std::string> arguments) {
    if(arguments.empty()){
        std::cout << "Who do you want to talk to?" << std::endl;
        return;
    }

    std::string npcName = arguments[arguments.size()-1];
    Room* room = player->getCurrentRoom();

    int px = player->getX();
    int py = player->getY();

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            auto npc = room->getNPCAt(px + dx, py + dy);

            if (npc && makeLowercase(npc->getName()) == npcName) {
                npc->talk();
                return;
            }
        }
    }
    std::cout << "Nobody by that name is nearby." << std::endl;
}

void ZOOrkEngine::handleEquipCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Equip what?\n";
        return;
    }
    player->equipItem(arguments[0]);
}

void ZOOrkEngine::handleUnequipCommand() {
    player->unequipItem();
}

void ZOOrkEngine::handleHelpCommand() {
    std::cout << "\n========== COMMAND LIST ==========\n";

    std::cout << "MOVEMENT:\n";
    std::cout << "  go north   | go n   -> Move north\n";
    std::cout << "  go south   | go s   -> Move south\n";
    std::cout << "  go east    | go e   -> Move east\n";
    std::cout << "  go west    | go w   -> Move west\n";
    std::cout << "  teleport <x> <y>    -> Teleport to (x,y)\n";

    std::cout << "\nLOOKING / INTERACTION:\n";
    std::cout << "  look | inspect -> Inspect the current room\n";
    std::cout << "  map            -> Show the room map again\n";
    std::cout << "  talk <npc>     -> Talk to a nearby NPC\n";

    std::cout << "\nITEM COMMANDS:\n";
    std::cout << "  take <item> | get <item>  -> Pick up an item\n";
    std::cout << "  drop <item>               -> Drop an item\n";
    std::cout << "  use <item>                -> Use an item\n";
    std::cout << "  equip <item>              -> Equip an item\n";
    std::cout << "  unequip                   -> Unequip current item\n";
    std::cout << "  inventory                 -> Show inventory\n";

    std::cout << "\nGAME:\n";
    std::cout << "  help        -> Show this command list\n";
    std::cout << "  quit | q    -> Quit the game\n";

    std::cout << "==================================\n";
}

void ZOOrkEngine::handleMapCommand(){
    player->getCurrentRoom()->render(player->getX(), player->getY(),
        player->getCurrentRoom()->getViewW(),
        player->getCurrentRoom()->getViewH());
    std::cout << "Player is now at: x = " << player->getX() << ", y = " << player->getY() << "\n";
}

void ZOOrkEngine::handleTeleportCommand(std::vector<std::string> arguments) {
    if (arguments.size() < 2) {
        std::cout << "Please use: teleport <x> <y>\n";
        return;
    }

    int x, y;
    try {
        x = std::stoi(arguments[0]);
        y = std::stoi(arguments[1]);
    }
    catch (...) {
        std::cout << "Invalid coordinates.\n";
        return;
    }

    Room* room = player->getCurrentRoom();
    if (x < 0 || x >= room->getWidth() ||  y < 0 || y >= room->getHeight()) {
        std::cout << "That position is outside the map.\n";
        return;
    }

    auto cell = room->getCell(x, y);
    if (!cell->isPassable()) {
        std::cout << "You cannot teleport there. It is not passable.\n";
        return;
    }
    if (room->getNPCAt(x, y)) {
        std::cout << "Someone is standing there.\n";
        return;
    }

    auto currentCell = room->getCell(player->getX(), player->getY());
    if (cell->getSymbol() != currentCell->getSymbol()) {
        std::cout << "Cannot teleport from " << currentCell->getRegionTag() 
            << " to " << cell->getRegionTag() << "\n";
        return;
    }

    player->setPosition(x, y);
    handleMapCommand();
    player->checkEquippedRegion();
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::getline(std::cin, input);
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }else{
        std::cout << "Enter your command to continue the game or type 'help'.\n";
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);
    return output;
}

std::shared_ptr<DoorCell> ZOOrkEngine::getNearbyDoor() {
    Room* room = player->getCurrentRoom();

    int x = player->getX();
    int y = player->getY();

    const int dx[] = {0, 0, 1, -1};
    const int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < room->getWidth() &&
            ny >= 0 && ny < room->getHeight()) {

            auto cell = room->getCell(nx, ny);
            auto door = std::dynamic_pointer_cast<DoorCell>(cell);
            if (door) {
                return door;
            }
        }
    }
    return nullptr;
}