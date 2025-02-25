target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/collider_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rect_collider_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/collision_manager.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
