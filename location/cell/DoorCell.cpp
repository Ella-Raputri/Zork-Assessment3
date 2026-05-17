#include "DoorCell.h"

DoorCell::DoorCell(std::shared_ptr<DoorState> state, const std::string& keyId)
    : Cell(
        CellType::Door,
        'd',
        "A door.",
        "door",
        true,
        Color::MAGENTA
    ),
      state(state),
      keyId(keyId)
{}

bool DoorCell::isLocked() const {
    return state->locked;
}

void DoorCell::lock() {
    state->locked = true;
}

void DoorCell::unlock() {
    state->locked = false;
}

bool DoorCell::canUnlockWith(const std::string& key) const {
    return key == keyId;
}

std::string DoorCell::getDescription() const {
    if (state->locked) {
        return "A locked door.";
    }
    return "An unlocked door.";
}

bool DoorCell::isPassable() const {
    return !state->locked;
}