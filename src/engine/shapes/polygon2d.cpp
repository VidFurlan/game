#include "polygon2d.hpp"
#include <GL/gl.h>
#include <iostream>


Polygon2D::Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos, glm::vec3 color)
	: Shape2D(pos, color) {
	this->vertices = vertices;
}

void Polygon2D::draw() const {
}
