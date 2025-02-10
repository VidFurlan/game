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
	mPos = glm::vec3(10.0f, 0.0f, 0.0f);
	AddChild((new SpriteSheetGameObject("PlayerSprite", this, "player", {16, 16}, glm::vec3(0.0f), {8, 8}))
	             ->SetScale(glm::vec2(1.0f))
	             ->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f)));
	AddChild(new GameObject("PlayerCollider", this));
}

void Player::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	animationTimeElapsed += deltaTime;
	if (animationTimeElapsed > 0.3f) {
		animationTimeElapsed = 0.0f;
		animationFrame = (animationFrame + 1) % 2;
		((SpriteSheetGameObject *)GetChild("PlayerSprite"))->SetSpriteSheetFrame({0, (animationFrame)});
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

    dashTimeElapsed += deltaTime;
    if (dashTimeElapsed > dashTime) {
        dashTimeElapsed = 0.0f;
        oldDir.x = -oldDir.x;
    }
	if (oldDir.x < 0) {
		((SpriteSheetGameObject *)GetChild("PlayerSprite"))->SetScale(glm::vec2(-1.0f, 1.0f));
	} else {
		((SpriteSheetGameObject *)GetChild("PlayerSprite"))->SetScale(glm::vec2(1.0f, 1.0f));
	}
}
