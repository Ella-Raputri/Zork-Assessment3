#ifndef ZOORK_DOORCELL_H
#define ZOORK_DOORCELL_H

#include "Cell.h"
#include "DoorState.h"

class DoorCell : public Cell {
private:
    std::shared_ptr<DoorState> state;
    std::string keyId;

public:
    DoorCell(
        std::shared_ptr<DoorState> state,
        const std::string& keyId = ""
    );

    bool isLocked() const;
    void lock();
    void unlock();

    bool canUnlockWith(const std::string& key) const;
    std::string getDescription() const override;
    bool isPassable() const override;
};

#endif