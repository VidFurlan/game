cmake_minimum_required(VERSION 3.12)
project(Game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets
)

add_subdirectory(libs/minifb)
add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

add_dependencies(${PROJECT_NAME} CopyAssets)
