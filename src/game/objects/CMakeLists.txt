target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/room_transition.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/menu_transition.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/saver.cpp
)

add_subdirectory(dungeon)
add_subdirectory(ui)
add_subdirectory(entities)
