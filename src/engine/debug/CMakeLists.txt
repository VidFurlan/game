target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug_shape_renderer.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
