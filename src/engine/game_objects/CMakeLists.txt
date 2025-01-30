target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scene_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera_game_object.cpp
)

add_subdirectory(drawables)
add_subdirectory(physics)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
