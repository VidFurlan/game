#include "polygon2d.hpp"
#include <GL/gl.h>
#include <iostream>
#include "debug_renderer.hpp"


Polygon2D::Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos, glm::vec3 color)
	: Shape2D(pos, color) {
	this->vertices = vertices;
}

void Polygon2D::draw() const {
    for (int i = 0; i < vertices.size(); i++) {
        DebugRenderer::GetInstance().drawLineGlobalPos(vertices[i], vertices[(i + 1) % vertices.size()], color);
    }
}
