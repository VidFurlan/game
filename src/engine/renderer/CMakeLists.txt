target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/game_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resource_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/post_processor.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
