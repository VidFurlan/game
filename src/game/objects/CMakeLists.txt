target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
)

add_subdirectory(dungeon)
add_subdirectory(ui)
add_subdirectory(entities)
