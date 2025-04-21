#pragma once

#include "objects/entities/entity.hpp"

class Chest : public Entity {
   public:
	Chest(std::string name, GameObject *parent, glm::vec3 position = glm::vec3(0.0f));
    ~Chest();
    virtual void Update(float deltaTime) override;

    virtual void Death() override;
};
