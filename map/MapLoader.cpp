// MapLoader.cpp
#include "MapLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> MapLoader::split(
    const std::string& line,
    char delimiter
) {
    std::vector<std::string> tokens;

    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string MapLoader::stringToColor(const std::string& str) {
    if (str == "WHITE") return Color::WHITE;
    if (str == "GREEN") return Color::GREEN;
    if (str == "BLUE") return Color::BLUE;
    if (str == "CYAN") return Color::CYAN;
    if (str == "BROWN") return Color::BROWN;
    if (str == "BRIGHT_BLACK") return Color::BRIGHT_BLACK;
    if (str == "BRIGHT_RED") return Color::BRIGHT_RED;
    return Color::WHITE;
}

CellType MapLoader::stringToCellType(const std::string& str) {
    if (str == "Floor") return CellType::Floor;
    if (str == "Restricted") return CellType::Restricted;
    if (str == "Impassable") return CellType::Impassable;
    return CellType::Floor;
}

std::vector<MapRegion> MapLoader::loadRegions(const std::string& filename) {
    std::vector<MapRegion> regions;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filename << std::endl;
        return regions;
    }

    std::string line;
    std::getline(file, line); //skip header

    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() < 11) continue;

        MapRegion region;
        region.name = tokens[0];

        region.startX = std::stoi(tokens[1]);
        region.startY = std::stoi(tokens[2]);
        region.endX = std::stoi(tokens[3]);
        region.endY = std::stoi(tokens[4]);

        region.symbol = tokens[5][0];
        region.color = stringToColor(tokens[6]);
        region.cellType = stringToCellType(tokens[7]);

        region.doorX = tokens[8].empty() ? -1 : std::stoi(tokens[8]);
        region.doorY = tokens[9].empty() ? -1 : std::stoi(tokens[9]);
        region.isSeparateRoom = (tokens[10] == "TRUE");

        region.requiredItem = tokens.size() > 11 ? tokens[11] : "";
        regions.push_back(region);
    }
    return regions;
}

void MapLoader::applyRegions(
    const std::shared_ptr<Room>& room,
    const std::vector<MapRegion>& regions
) {
    for (const auto& region : regions) {
        for (int y = region.startY; y <= region.endY; y++) {
            for (int x = region.startX; x <= region.endX; x++) {

                if (region.cellType == CellType::Restricted) {
                    room->setRestrictedCell(
                        x,
                        y,
                        region.symbol,
                        "You are in " + region.name,
                        region.name,
                        region.requiredItem,
                        "Restricted area: Need " + region.requiredItem,
                        region.color
                    );
                }
                else {
                    bool walkable = region.cellType != CellType::Impassable;
                    room->setCell(
                        x,
                        y,
                        region.cellType,
                        region.symbol,
                        "You are in " + region.name,
                        region.name,
                        walkable,
                        region.color
                    );
                }
            }
        }
    }
}

std::unordered_map<std::string, std::shared_ptr<Room>> MapLoader::createSeparateRooms(
    const std::vector<MapRegion>& regions
) {
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;

    for (const auto& region : regions) {
        if (!region.isSeparateRoom) continue;

        int width  = region.endX - region.startX + 1;
        int height = region.endY - region.startY + 1;

        auto room = std::make_shared<Room>(
            region.name, "Inside " + region.name,
            width, height, width, height
        );

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                room->setCell(
                    x,
                    y,
                    region.cellType,
                    region.symbol,
                    "Inside " + region.name,
                    region.name,
                    true,
                    region.color
                );
            }
        }
        rooms[region.name] = room;
    }
    return rooms;
}

void MapLoader::connectSeparateRooms(
    const std::shared_ptr<Room>& outside,
    const std::vector<MapRegion>& regions,
    std::unordered_map<
        std::string,
        std::shared_ptr<Room>
    >& interiors
) {
    for (const auto& region : regions) {
        if (!region.isSeparateRoom) continue;

        auto inside = interiors[region.name];
        auto doorState = std::make_shared<DoorState>(true);

        outside->setDoorCell(
            region.doorX,
            region.doorY,
            doorState,
            ""
        );

        int insideDoorX = inside->getWidth() / 2;
        int insideDoorY = inside->getHeight() - 1;

        inside->setDoorCell(
            insideDoorX,
            insideDoorY,
            doorState,
            ""
        );

        Passage::createBasicPassage(
            outside.get(),
            inside.get(),
            "enter",

            region.doorX,
            region.doorY,

            insideDoorX,
            insideDoorY,

            region.doorX,
            region.doorY + 1,

            insideDoorX,
            insideDoorY - 1,

            true
        );
    }
}