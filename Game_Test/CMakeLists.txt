cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

project(Game_Test)

add_executable( ${PROJECT_NAME} main.cpp )
link_directories( /usr/local/lib )
include_directories(
        /usr/local/include
)

find_package( SDL2 REQUIRED )
find_package( SDL2_image REQUIRED )
find_package( SDL2_TTF REQUIRED )
find_package( GLM REQUIRED )
find_package( Lua REQUIRED )

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libRGE.a)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/liblua.a)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libtmxlite.dylib)
