#pragma once

#include "objects/entities/entity.hpp"

class Enemy : public Entity {
   public:
	Enemy(std::string name, GameObject *parent, glm::vec3 position = glm::vec3(0.0f));

	void Update(float deltaTime) override;

	void Damage(int damage);

   private:
	int mMaxHealth = 3;
	int mHealth = mMaxHealth;
	float moveSpeed = 20.0f;

    float mAnimationTimeElapsed = 0.0f;
    int mAnimationFrame = 0;
};
