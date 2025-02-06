target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
)

add_subdirectory(game_objects)
add_subdirectory(renderer)
add_subdirectory(utils)
add_subdirectory(debug)
add_subdirectory(shapes)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
