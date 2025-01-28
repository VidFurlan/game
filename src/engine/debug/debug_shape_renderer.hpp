#pragma once

#include "game_window.hpp"
#include "resource_manager.hpp"

class DebugShapeRenderer {
private:
    GLuint VAO, VBO;
    Shader lineShader;

public:
    DebugShapeRenderer();
    ~DebugShapeRenderer();

    void drawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color);
    void render();
};
