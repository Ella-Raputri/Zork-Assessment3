#ifndef ZOORK_RESTRICTEDCELL_H
#define ZOORK_RESTRICTEDCELL_H

#include "Cell.h"
#include <string>

class RestrictedCell : public Cell {
private:
    std::string requiredItemId;
    std::string failMessage;

public:
    RestrictedCell(
        char symbol,
        const std::string& description,
        const std::string& regionTag,
        const std::string& requiredItemId,
        const std::string& failMessage,
        const std::string& color
    );

    const std::string& getRequiredItemId() const;
    const std::string& getFailMessage() const;
};

#endif