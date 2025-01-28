#pragma once

#include <vector>

#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Shape2D {
   public:
	Shape2D(glm::vec2 pos = glm::vec2(0.0f), glm::vec3 color = glm::vec3(1.0f)) : pos(pos), color(color) {}
	virtual void draw() const = 0;

   protected:
	glm::vec2 pos;
	glm::vec3 color;
	std::vector<glm::vec2> vertices;
};
