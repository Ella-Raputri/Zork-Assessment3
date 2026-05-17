#ifndef DOORSTATE_H
#define DOORSTATE_H

class DoorState {
public:
    bool locked;

    DoorState(bool locked = false)
        : locked(locked) {}
};

#endif