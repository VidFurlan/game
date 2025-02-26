#pragma once

#include "collider_game_object.hpp"
#include "game_object.hpp"
#include "game_scene.hpp"
#include "objects/entities/entity.hpp"

class Player : public Entity {
	friend class PlayerUI;

   public:
	Player(std::string name, GameObject *parent, glm::vec3 position = glm::vec3(0.0f));
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;

	void Damage(int damage);

   private:
	int mMaxHealth = 6;
	int mHealth = mMaxHealth;

	float animationTimeElapsed = 0.0f;
	int animationFrame = 0;

	float moveSpeed = 40.0f;
	bool dash = false;
	bool dashCooldown = false;
	float dashSpeed = 300.0f;
	float dashTimeElapsed = 0.0f;
	float dashTime = 0.1f;
	float dashCooldownTime = 0.5f;
	float dashCooldownElapsed = 0.0f;
	glm::vec2 dashDir;
	glm::vec2 oldDir;
};
