#include "player.hpp"

#include <iostream>

#include "GLFW/glfw3.h"
#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

Player::Player(std::string name, GameObject *parent, glm::vec3 position)
    : GameObject(name, parent, position) {
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
    SetZIndex(1001);
    (new SpriteSheetGameObject("PlayerSprite", this, "player", {16, 16}, {0, 0, 0}, {8, 8}))
        ->SetSpriteSheetFrame({0, 0});
}

void Player::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	animationTimeElapsed += deltaTime;
	if (animationTimeElapsed > 0.3f) {
		animationTimeElapsed = 0.0f;
		animationFrame = (animationFrame + 1) % 2;
		((SpriteSheetGameObject *)GetChild("PlayerSprite"))->SetSpriteSheetFrame({0, animationFrame});
	}

	glm::vec2 movement = glm::vec2(0.0f);
	if (Game::GetInstance().Keys[GLFW_KEY_W]) movement.y -= 1.0f;
	if (Game::GetInstance().Keys[GLFW_KEY_S]) movement.y += 1.0f;
	if (Game::GetInstance().Keys[GLFW_KEY_A]) movement.x -= 1.0f;
	if (Game::GetInstance().Keys[GLFW_KEY_D]) movement.x += 1.0f;
	if (movement.x != 0 || movement.y != 0) movement = glm::normalize(movement);

	if (dashCooldown) {
		dashCooldownElapsed += deltaTime;
		if (dashCooldownElapsed > dashCooldownTime) {
			dashCooldown = false;
			dashCooldownElapsed = 0.0f;
		}
	}

	if (Game::GetInstance().Keys[GLFW_KEY_SPACE] && !dash && !dashCooldown) {
		dashDir = movement;
		dash = true;
	}

	if (dash) {
		dashTimeElapsed += deltaTime;
		if (dashTimeElapsed > dashTime) {
			dash = false;
			dashCooldown = true;
			dashTimeElapsed = 0.0f;
		}
		*((GameObject *)this) += dashDir * dashSpeed * deltaTime;
	} else {
		*((GameObject *)this) += movement * moveSpeed * deltaTime;
	}

	Game::GetInstance().GetActiveScene()->GetActiveCamera()->SetPosition(glm::vec3((glm::vec2)this->GetPosition(), 0.0f));

	if (movement.x != 0) {
		oldDir = movement;
	}

	if (oldDir.x < 0) {
		((SpriteSheetGameObject *)GetChild("PlayerSprite"))->SetScale(glm::vec2(-8.0f, 8.0f));
	} else {
		((SpriteSheetGameObject *)GetChild("PlayerSprite"))->SetScale(glm::vec2(8.0f, 8.0f));
	}
}
