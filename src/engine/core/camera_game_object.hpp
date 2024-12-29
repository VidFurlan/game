#pragma once

#include "game_object.hpp"

class CameraGameObject : public GameObject {
   public:
    CameraGameObject(std::string name, glm::vec3 pos = glm::vec3(0.0f));
    CameraGameObject(std::string name, GameObject *parent, glm::vec3 pos = glm::vec3(0.0f));

    ~CameraGameObject();
};
