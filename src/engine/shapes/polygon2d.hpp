#pragma once

#include "glm/fwd.hpp"
#include "shapes/shape2d.hpp"

class Polygon2D : public Shape2D {
    public:
        Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos = glm::vec2(0.0f), glm::vec3 color = glm::vec3(1.0f));
        void draw() const override;
};
