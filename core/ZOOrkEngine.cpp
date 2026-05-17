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
        std::cout << "> ";

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
        } else if (command == "inventory") {
            handleInventoryCommand();
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

    std::string reason = currentRoom->canMoveTo(currX, currY, newX, newY, direction);

    if (!reason.empty()) {
        std::cout << reason << std::endl;
        return;
    }

    if (currentRoom->getCell(newX, newY).getType() == CellType::Door) {
        auto passage = currentRoom->getPassage(direction);
        if (passage->getName() == "null") {
            passage = currentRoom->getPassageByPosition(newX, newY);
        }
        if (passage->getName() != "null") {
            std::cout<<"hehe"<< std::endl;
            passage->enter();
            player->setCurrentRoom(passage->getTo());
            player->setPosition(passage->getArriveX(), passage->getArriveY());
        }
    } else {
        player->setPosition(newX, newY);
        std::cout << currentRoom->getCell(newX, newY).getDescription() << "\n";
    }

    player->getCurrentRoom()->render(player->getX(), player->getY(),
        player->getCurrentRoom()->getViewW(),
        player->getCurrentRoom()->getViewH());
    // in handleGoCommand after passage fires
    std::cout << "DEBUG arrived at: " << player->getX() << "," << player->getY() << "\n";
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    std::cout << player->getCurrentRoom()->getDescription() << std::endl;

    Room* currentRoom = player->getCurrentRoom();
    int currX = player->getX();
    int currY = player->getY();
    Cell& cell = currentRoom->getCell(currX, currY);

    if (cell.hasItems()) {
        std::cout << "You see: " << std::endl;
        for (const auto& item : cell.getItems()) {
            std::cout << "- " << item->getName()
                      << ": " << item->getDescription() << std::endl;
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

    Cell& cell = currentRoom->getCell(currX, currY);
    auto item = cell.retrieveItem(arguments[0]);

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

    Cell& cell = currentRoom->getCell(currX, currY);
    auto item = player->getItem(arguments[0]);

    if (item) {
        cell.addItem(item);
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

    if (item->getType() == ItemType::Key) {
        if (!isNearDoor()) {
            std::cout << "There is no door nearby to use the key on." << std::endl;
            return;
        }
        std::cout << "You use the key on the door." << std::endl;
    }

    item->use();
    if (item->isDepleted()) {
        player->removeItem(arguments[0]);
        std::cout << "The " << item->getName() << " is depleted and can not be used anymore." << std::endl;
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
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

bool ZOOrkEngine::isNearDoor() {
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

            if (room->getCell(nx, ny).getType() == CellType::Door) {
                return true;
            }
        }
    }
    return false;
}