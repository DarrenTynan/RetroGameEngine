cmake_minimum_required(VERSION 3.24)
project(RetroGameEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        main.cpp
        Game/src/Game.h
        Game/src/Game.cpp
        )
