#pragma once

#include "objects/entities/entity.hpp"
#include "objects/ui/player_ui.hpp"

class Enemy : public Entity {
   public:
	Enemy(std::string name, GameObject *parent, glm::vec3 position = glm::vec3(0.0f));
    ~Enemy();

	void Update(float deltaTime) override;

    virtual void Death() override;

   private:
	float moveSpeed = 20.0f;

	float mAnimationTimeElapsed = 0.0f;
	int mAnimationFrame = 0;
};
