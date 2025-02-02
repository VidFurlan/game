#pragma once

#include <vector>
#include "glm/fwd.hpp"
#include "shapes/shape2d.hpp"

class Polygon2D : public Shape2D {
    public:
        Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos = glm::vec2(0.0f), glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f));

        void DrawDebug(glm::vec2 offset = glm::vec2(0.0f), float rot = 0.0f, glm::vec2 scale = glm::vec2(1.0f)) const override;
        bool CheckOverlap(const glm::vec3 &thisGlobalPos, const Shape2D *other, const glm::vec3 &otherGlobalPos) const override;
        std::vector<glm::vec2> GetEdges(glm::vec3 pos = glm::vec3(0.0f)) const override;
};
