#include "Cell.h"

Cell::Cell()
    : type(CellType::Empty),
      symbol('x'),
      description("You are in the garden."),
      regionTag("garden"),
      passable(true) {}

Cell::Cell(
    CellType type,
    char symbol,
    const std::string& description,
    const std::string& regionTag,
    bool passable,
    const std::string& color
)
    : type(type),
      symbol(symbol),
      description(description),
      regionTag(regionTag),
      passable(passable),
      color(color) {}

CellType Cell::getType() const {
    return type;
}

char Cell::getSymbol() const {
    return symbol;
}

std::string Cell::getDescription() const {
    return description;
}

std::string Cell::getRegionTag() const {
    return regionTag;
}

bool Cell::isPassable() const {
    return passable;
}

std::string Cell::getColor() const {
    return color;
}

void Cell::setType(CellType t) {
    type = t;
}

void Cell::setSymbol(char s) {
    symbol = s;
}

void Cell::setDescription(const std::string& d) {
    description = d;
}

void Cell::setRegionTag(const std::string& r) {
    regionTag = r;
}

void Cell::setPassable(bool p) {
    passable = p;
}

void Cell::setColor(const std::string& c){
    color = c;
}