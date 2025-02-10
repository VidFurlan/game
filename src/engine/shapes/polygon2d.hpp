#pragma once

#include <vector>

#include "glm/ext/vector_float4.hpp"
#include "glm/fwd.hpp"
#include "shapes/shape2d.hpp"

class Polygon2D : public Shape2D {
   public:
	Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos = glm::vec2(0.0f), glm::vec4 color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	void DrawDebug(glm::vec2 offset = glm::vec2(0.0f), float rot = 0.0f, glm::vec2 scale = glm::vec2(1.0f)) const override;
	std::vector<glm::vec2> GetEdges(glm::vec3 pos = glm::vec3(0.0f)) const override;
	std::vector<glm::vec2> GetVertices(glm::vec3 pos = glm::vec3(0.0f)) const override;
};
