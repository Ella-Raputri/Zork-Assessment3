cmake_minimum_required(VERSION 3.23)
project(ZOOrk)

set(CMAKE_CXX_STANDARD 20)

add_executable(ZOOrk
    utils/Color.h
    entity/GameObject.cpp
    entity/GameObject.h

    command/Command.h
    entity/item/Item.h
    entity/item/Item.cpp
    entity/item/UsableItem.h
    entity/item/UsableItem.cpp
    entity/item/EquippableItem.h
    entity/item/EquippableItem.cpp
    entity/item/ClueItem.h
    entity/item/ClueItem.cpp

    location/Location.cpp
    location/Location.h
    location/cell/Cell.cpp
    location/cell/Cell.h
    location/cell/DoorState.h
    location/cell/DoorCell.cpp
    location/cell/DoorCell.h
    location/cell/RestrictedCell.cpp
    location/cell/RestrictedCell.h

    location/room/Room.cpp
    location/room/Room.h
    location/passage/Passage.cpp
    location/passage/Passage.h

    location/room/NullRoom.cpp
    location/room/NullRoom.h
    location/passage/NullPassage.cpp
    location/passage/NullPassage.h

    command/NullCommand.cpp
    command/NullCommand.h
    command/RoomDefaultEnterCommand.cpp
    command/RoomDefaultEnterCommand.h
    command/PassageDefaultEnterCommand.cpp
    command/PassageDefaultEnterCommand.h

    entity/character/Character.cpp
    entity/character/Character.h
    entity/character/Player.cpp
    entity/character/Player.h
    entity/character/NPC.cpp
    entity/character/NPC.h
    map/MapLoader.cpp
    map/MapLoader.h

    core/ZOOrkEngine.cpp
    core/ZOOrkEngine.h
    main.cpp
)