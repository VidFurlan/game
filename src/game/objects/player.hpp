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

   private:
    void Attack(float deltaTime);

	float animationTimeElapsed = 0.0f;
	int animationFrame = 0;

    bool attacking = false;
    bool attackingCooldown = false;
    Direction attackDir;
    float attackTime = 0.2f;
    float attackDelay = 0.2f;
    int attackDamage = 1;
    float attackTimeElapsed = 0.0f;

	float moveSpeed = 35.0f;
	bool dash = false;
	bool dashCooldown = false;
	float dashSpeed = 120.0f;
	float dashTimeElapsed = 0.0f;
	float dashTime = 0.13f;
	float dashCooldownTime = 0.5f;
	float dashCooldownElapsed = 0.0f;
	glm::vec2 dashDir;
	glm::vec2 oldDir;
};
