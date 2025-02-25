#include "rect_collider_game_object.hpp"
#include "polygon2d.hpp"

RectColliderGameObject::RectColliderGameObject(std::string name, bool fixed, glm::vec3 pos, glm::vec2 scale) : ColliderGameObject(name, new Polygon2D({{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}}), fixed, pos, scale) {
}

RectColliderGameObject::RectColliderGameObject(std::string name, GameObject *parent, bool fixed, glm::vec3 pos, glm::vec2 scale) : ColliderGameObject(name, parent, new Polygon2D({{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}}), fixed, pos, scale) {
}
