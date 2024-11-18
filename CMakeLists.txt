cmake_minimum_required(VERSION 3.24)
project(RetroGameEngine)

set(CMAKE_CXX_STANDARD 23)

#add_library(test_library STATIC RGE/src/RGE.cpp)
add_library(RGE STATIC RGE/src/RGE.cpp)
#add_library(_RGE STATIC RGE/src/RGE.cpp)

add_executable(${PROJECT_NAME}
        main.cpp
        Game/src/Game.cpp
        )

#target_link_libraries(${PROJECT_NAME} RGE)

#find_package(RGE REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
