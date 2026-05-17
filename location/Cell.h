#ifndef ZOORK_CELLTYPE_H
#define ZOORK_CELLTYPE_H

#include <string>
#include "../utils/Color.h"

enum class CellType {
    Empty,   // 'x' - outside/garden
    Floor,   // 'h' - interior
    Door,    // 'd' - transition point
    Impassable,    // '#' - impassable
};

class Cell {
    protected: 
        CellType type;
        char symbol;
        std::string description;
        std::string regionTag;  // e.g. "house", "garden"
        bool passable;
        std::string color;

    public: 
        Cell();

        Cell(
            CellType type,
            char symbol,
            const std::string& description,
            const std::string& regionTag,
            bool passable,
            const std::string& color
        );

        CellType getType() const;
        char getSymbol() const;
        std::string getDescription() const;
        std::string getRegionTag() const;
        bool isPassable() const;
        std::string getColor() const;

        void setType(CellType);
        void setSymbol(char);
        void setDescription(const std::string&);
        void setRegionTag(const std::string&);
        void setPassable(bool);
        void setColor(const std::string&);
};

#endif //ZOORK_CELLTYPE_H