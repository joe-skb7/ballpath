cmake_minimum_required(VERSION 2.8)
set(PROJECT ballpath)
project(${PROJECT})

# set(CMAKE_BUILD_TYPE Debug)

include_directories(src)
set(SOURCES
    src/main.cpp
    src/appcontroller.cpp
    src/inputreader.cpp
    src/resultwriter.cpp
    src/core/gamemap.cpp
    src/core/node.cpp
    src/core/nodeiterator.cpp
    src/core/pathfinder.cpp
    src/util/point.cpp
    src/util/size.cpp
)
set(HEADERS
    src/appcontroller.h
    src/inputreader.h
    src/resultwriter.h
    src/core/action.h
    src/core/gamemap.h
    src/core/node.h
    src/core/nodeiterator.h
    src/core/pathfinder.h
    src/util/math.h
    src/util/point.h
    src/util/size.cpp
)

add_definitions(-std=c++0x -Wall -pedantic -O2)
add_executable(${PROJECT} ${SOURCES} ${HEADERS})

install(TARGETS ${PROJECT} DESTINATION bin)
