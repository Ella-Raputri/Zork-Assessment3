cmake_minimum_required(VERSION 3.23)
project(ZOOrk)

set(CMAKE_CXX_STANDARD 20)

add_executable(ZOOrk
    entity/GameObject.cpp
    entity/GameObject.h

    command/Command.h
    entity/Item.h
    entity/Item.cpp

    location/Location.cpp
    location/Location.h
    location/Cell.cpp
    location/Cell.h

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

    entity/Character.cpp
    entity/Character.h
    entity/Player.cpp
    entity/Player.h

    core/ZOOrkEngine.cpp
    core/ZOOrkEngine.h
    main.cpp
)