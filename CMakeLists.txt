cmake_minimum_required(VERSION 3.10)

project(Game_Minesweeper)

# Find SDL2 library
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add executable
add_executable(Game_Minesweeper main.cpp)
target_link_libraries(Game_Minesweeper ${SDL2_LIBRARIES})