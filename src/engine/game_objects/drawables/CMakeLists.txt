target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/drawable_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/abstract_image_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/spritesheet_game_object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text_game_object.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
