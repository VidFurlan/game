#pragma once

#include "shapes/shape2d.hpp"

class Polygon2D : public Shape2D {
    public:
        Polygon2D(std::vector<glm::vec2> vertices, glm::vec2 pos, glm::vec3 color);
        void draw() const override;
};
