#ifndef ZOORK_MAPLOADER_H
#define ZOORK_MAPLOADER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>  

#include "../utils/Color.h"
#include "../location/cell/Cell.h"
#include "../location/room/Room.h"
#include "../location/passage/Passage.h"

struct MapRegion {
    std::string name;

    int startX;
    int startY;
    int endX;
    int endY;

    char symbol;

    std::string color;
    CellType cellType;

    int doorX;
    int doorY;

    bool isSeparateRoom;
    std::string requiredItem;
    std::string keyId;
    std::string doorDirection;
};


class MapLoader {
public:
    static std::vector<MapRegion> loadRegions(const std::string& filename);

    static void applyRegions(
        const std::shared_ptr<Room>& room,
        const std::vector<MapRegion>& regions
    );

    static std::unordered_map<std::string, std::shared_ptr<Room>> createSeparateRooms(
        const std::vector<MapRegion>& regions
    );

    static void connectSeparateRooms(
        const std::shared_ptr<Room>& outside,
        const std::vector<MapRegion>& regions,
        std::unordered_map<
            std::string,
            std::shared_ptr<Room>
        >& interiors
    );

private:
    static std::vector<std::string> split(const std::string& line, char delimiter);
    static std::string stringToColor(const std::string& str);
    static CellType stringToCellType(const std::string& str);
};


#endif //ZOORK_MAPLOADER_H