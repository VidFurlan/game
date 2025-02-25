#pragma once

#include "collider_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float3.hpp"

class RectColliderGameObject : public ColliderGameObject {
   public:
    RectColliderGameObject(std::string name, bool fixed, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
    RectColliderGameObject(std::string name, GameObject *parent, bool fixed, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
    ~RectColliderGameObject();
    
    using ColliderGameObject::Update;
    using ColliderGameObject::Render;
};
