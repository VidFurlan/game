cmake_minimum_required(VERSION 3.12)
project(Game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_subdirectory(libs/minifb)

add_subdirectory(src)
