#pragma once

#include <set>
#include <vector>

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class Shape2D {
   public:
	Shape2D(glm::vec2 pos = glm::vec2(0.0f), glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f))
		: pos(pos), color(color) {}
	virtual ~Shape2D() = default;

	virtual void DrawDebug(glm::vec2 offset = glm::vec2(0.0f), float rot = 0.0f) const = 0;
	virtual bool CheckOverlap(const glm::vec3 &thisGlobalPos, const Shape2D *other, const glm::vec3 &otherGlobalPos) const = 0;

   protected:
	glm::vec2 pos;
	glm::vec3 color;
	std::vector<glm::vec2> vertices;
};
