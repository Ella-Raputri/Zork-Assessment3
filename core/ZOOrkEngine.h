//
// Created by Richard Skarbez on 5/7/23.
// Modified by Ella Raputri on 5/16/26
//

#ifndef ZOORK_ZOORKENGINE_H
#define ZOORK_ZOORKENGINE_H

#include "../entity/Player.h"
#include "../location/Location.h"
#include "../location/passage/Passage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

class ZOOrkEngine {
public:
    ZOOrkEngine(std::shared_ptr<Room>, int startX, int startY);

    void run();

private:
    bool gameOver = false;
    Player *player;

    void handleGoCommand(std::vector<std::string>);
    void handleLookCommand(std::vector<std::string>);

    void handleTakeCommand(std::vector<std::string>);
    void handleDropCommand(std::vector<std::string>);
    void handleUseCommand(std::vector<std::string>);

    void handleQuitCommand(std::vector<std::string>);

    static std::vector<std::string> tokenizeString(const std::string&);
    static std::string makeLowercase(std::string);
};


#endif //ZOORK_ZOORKENGINE_H
