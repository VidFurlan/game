#include "polygon2d.hpp"

#include <GL/gl.h>

#include "debug_renderer.hpp"

Polygon2D::Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos, glm::vec3 color)
	: Shape2D(pos, color) {
	this->vertices = vertices;
}

void Polygon2D::DrawDebug(glm::vec2 offset, float rot, glm::vec2 scale) const {
	float rotRad = glm::radians(rot);
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec2 p1 = vertices[i] * scale;
		glm::vec2 p2 = vertices[(i + 1) % vertices.size()] * scale;

		p1 = glm::vec2(p1.x * cos(rotRad) - p1.y * sin(rotRad), p1.x * sin(rotRad) + p1.y * cos(rotRad));
		p2 = glm::vec2(p2.x * cos(rotRad) - p2.y * sin(rotRad), p2.x * sin(rotRad) + p2.y * cos(rotRad));

		p1 += pos + offset;
		p2 += pos + offset;

		DebugRenderer::GetInstance().drawLineGlobalPos(p1, p2, color);
	}
}

bool Polygon2D::CheckOverlap(const glm::vec3 &thisGlobalPos, const Shape2D *other, const glm::vec3 &otherGlobalPos) const {
	if (other == nullptr) {
		return false;
	}

	float distance = glm::distance(thisGlobalPos, otherGlobalPos);

	if (distance < 30.0f) {
		return true;
	}

	return false;
}
