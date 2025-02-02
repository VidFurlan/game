#include "polygon2d.hpp"

#include <GL/gl.h>

#include "debug_renderer.hpp"
#include "glm/gtc/type_ptr.hpp"

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

std::vector<glm::vec2> Polygon2D::GetEdges(glm::vec3 pos) const {
    float rotRad = glm::radians(pos.z);
    std::vector<glm::vec2> edges;
    for (int i = 0; i < vertices.size(); i++) {
        glm::vec2 p1 = vertices[i];
        glm::vec2 p2 = vertices[(i + 1) % vertices.size()];

        p1 = glm::vec2(p1.x * cos(rotRad) - p1.y * sin(rotRad), p1.x * sin(rotRad) + p1.y * cos(rotRad));
        p2 = glm::vec2(p2.x * cos(rotRad) - p2.y * sin(rotRad), p2.x * sin(rotRad) + p2.y * cos(rotRad));

        p1 += glm::make_vec2(pos);
        p2 += glm::make_vec2(pos);

        edges.push_back(p2 - p1);
    }
    return edges;
}

std::vector<glm::vec2> Polygon2D::GetVertices(glm::vec3 pos) const {
    float rotRad = glm::radians(pos.z);
    std::vector<glm::vec2> vertices;
    for (int i = 0; i < this->vertices.size(); i++) {
        glm::vec2 p = this->vertices[i];
        p = glm::vec2(p.x * cos(rotRad) - p.y * sin(rotRad), p.x * sin(rotRad) + p.y * cos(rotRad));
        p += glm::make_vec2(pos);
        vertices.push_back(p);
    }
    return vertices;
}
