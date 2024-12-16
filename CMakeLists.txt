cmake_minimum_required(VERSION 3.12)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)

add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/bin/assets
)

set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/shaders)

add_custom_target(CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADERS_DIR} ${CMAKE_BINARY_DIR}/bin/shaders
)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

add_dependencies(${PROJECT_NAME} CopyAssets)
add_dependencies(${PROJECT_NAME} CopyShaders)
