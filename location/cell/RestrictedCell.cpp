#include "RestrictedCell.h"

RestrictedCell::RestrictedCell(
    char symbol,
    const std::string& description,
    const std::string& regionTag,
    const std::string& requiredItemId,
    const std::string& failMessage,
    const std::string& color
): Cell(
        CellType::Restricted,
        symbol,
        description,
        regionTag,
        true,
        color
    ),
      requiredItemId(requiredItemId),
      failMessage(failMessage)
{}

const std::string& RestrictedCell::getRequiredItemId() const {
    return requiredItemId;
}

const std::string& RestrictedCell::getFailMessage() const {
    return failMessage;
}