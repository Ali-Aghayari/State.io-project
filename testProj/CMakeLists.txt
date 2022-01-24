cmake_minimum_required(VERSION 3.21)
project(testProj C)

set(CMAKE_C_STANDARD 11)

add_executable(testProj main.c)
include_directories("/usr/include/SDL2")
target_link_libraries(testProj m SDL2 SDL2_gfx)

