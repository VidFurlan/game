#include "player.hpp"

#include <iostream>

#include "GLFW/glfw3.h"
#include "collider_game_object.hpp"
#include "collision_manager.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "objects/entities/entity.hpp"
#include "objects/menu_transition.hpp"
#include "objects/saver.hpp"
#include "polygon2d.hpp"
#include "rect_collider_game_object.hpp"
#include "spritesheet_game_object.hpp"

const float hitboxSize = 2.5f;
const float hitboxCorner = 0.9f;
const float slashSize = 5.0f;

Player::Player(std::string name, GameObject *parent, glm::vec3 position) : Entity(name,
                                                                                  parent,
                                                                                  EntityType::PLAYER,
                                                                                  new Polygon2D({{-hitboxSize + hitboxCorner, -hitboxSize},
                                                                                                 {-hitboxSize, -hitboxSize + hitboxCorner},
                                                                                                 {-hitboxSize, hitboxSize - hitboxCorner},
                                                                                                 {-hitboxSize + hitboxCorner, hitboxSize},
                                                                                                 {hitboxSize - hitboxCorner, hitboxSize},
                                                                                                 {hitboxSize, hitboxSize - hitboxCorner},
                                                                                                 {hitboxSize, -hitboxSize + hitboxCorner},
                                                                                                 {hitboxSize - hitboxCorner, -hitboxSize}}),
                                                                                  position,
                                                                                  {1.0f, 1.0f}) {
	mMaxHealth = 6;
	mHealth = mMaxHealth;
	mImmunityTime = 1.0f;
	SetZIndex(900);

	(new RectColliderGameObject("Hitbox", this, false, {0.0f, 0.0f, 0.0f}, {hitboxSize * 2, hitboxSize * 2}))
	    ->SetOnCollision([this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (other->GetParent()->GetName() == "Player") return;
		    if (other->GetTag() == "Enemy") {
			    Damage(1);
		    }
	    })
	    ->SetTag("Enemy");

	(new SpriteSheetGameObject("Sprite", this, "player", {16, 16}, {0.0f, -2.2f, 0.0f}, {8, 8}))
	    ->SetSpriteSheetFrame({0, 0});

	(new SpriteSheetGameObject("SlashSpriteH", this, "horizontal_slash_1", {1, 5}, {0.0f, 0.0f, 0.0f}, {16, 16}))
	    ->SetSpriteSheetFrame({0, 0})
	    ->SetVisible(false);
	(new SpriteSheetGameObject("SlashSpriteV", this, "horizontal_slash_1", {1, 5}, {0.0f, 0.0f, 90.0f}, {16, 16}))
	    ->SetSpriteSheetFrame({0, 0})
	    ->SetVisible(false);
	(new ColliderGameObject("SlashHitbox", this, new Polygon2D({{0.0f, -slashSize}, {-3.0f, -slashSize}, {-3.0f, slashSize}, {0.0f, slashSize}, {slashSize * 0.7, slashSize * 0.7}, {slashSize + slashSize * 0.3, 0.0f}, {slashSize * 0.7, -slashSize * 0.7}}), false))
	    ->SetOnCollision([this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (other->GetParent()->GetName() == "Player") return;
		    ((Entity *)other)->Damage(1);
	    })
	    ->SetTag("Enemy")
	    ->SetActive(false);
}

void Player::Update(float deltaTime) {
	Entity::Update(deltaTime);

	if (mActive == false) {
		return;
	}

	animationTimeElapsed += deltaTime;
	if (animationTimeElapsed > 0.3f) {
		animationTimeElapsed = 0.0f;
		animationFrame = (animationFrame + 1) % 2;
		((SpriteSheetGameObject *)GetChild("Sprite"))->SetSpriteSheetFrame({0, animationFrame});
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
		mPos += glm::make_vec3(dashDir * dashSpeed * deltaTime);
	} else {
		mPos += glm::make_vec3(movement * moveSpeed * deltaTime);
	}

	if (movement.x != 0) {
		oldDir = movement;
	}

	if (oldDir.x < 0) {
		((SpriteSheetGameObject *)GetChild("Sprite"))->SetScale(glm::vec2(-8.0f, 8.0f));
	} else {
		((SpriteSheetGameObject *)GetChild("Sprite"))->SetScale(glm::vec2(8.0f, 8.0f));
	}

	Attack(deltaTime);
}

void Player::Attack(float deltaTime) {
	ColliderGameObject *slashHitbox = (ColliderGameObject *)GetChild("SlashHitbox");
	if (attacking) {
		attackTimeElapsed += deltaTime;
		if (attackDir == Direction::RIGHT) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteH"))->SetSpriteSheetFrame({0, attackTimeElapsed / attackTime * 4})->SetPosition({3.0f, 0.0f});
		}
		if (attackDir == Direction::LEFT) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteH"))->SetSpriteSheetFrame({0, attackTimeElapsed / attackTime * 4})->SetPosition({-3.0f, 0.0f});
		}
		if (attackDir == Direction::UP) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteV"))->SetSpriteSheetFrame({0, attackTimeElapsed / attackTime * 4})->SetPosition({0.0f, -3.0f});
		}
		if (attackDir == Direction::DOWN) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteV"))->SetSpriteSheetFrame({0, attackTimeElapsed / attackTime * 4})->SetPosition({0.0f, 3.0f});
		}

		if (attackTimeElapsed > attackTime) {
			GetChild("SlashSpriteH")->SetVisible(false);
			GetChild("SlashSpriteV")->SetVisible(false);
			attackTimeElapsed = 0.0f;
			attacking = false;
			attackingCooldown = true;
			slashHitbox->SetActive(false);
		}
	} else {
		attackTimeElapsed += deltaTime;
		if (attackTimeElapsed > attackDelay) {
			attackingCooldown = false;
		}
		if (attackingCooldown) return;

		constexpr float slashHitboxOffset = 3.5f;
		if (Game::GetInstance().Keys[GLFW_KEY_RIGHT]) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteH"))
			    ->SetScale(glm::vec2(16.0f, 16.0f))
			    ->SetVisible(true);
			attacking = true;
			attackDir = Direction::RIGHT;
			attackTimeElapsed = 0.0f;
			slashHitbox
			    ->SetPosition({slashHitboxOffset, 0.0f, 0.0f})
			    ->SetRotation(0.0f)
			    ->SetActive(true);
		}
		if (Game::GetInstance().Keys[GLFW_KEY_LEFT]) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteH"))
			    ->SetScale(glm::vec2(-16.0f, 16.0f))
			    ->SetVisible(true);
			attacking = true;
			attackDir = Direction::LEFT;
			attackTimeElapsed = 0.0f;
			slashHitbox
			    ->SetPosition({-slashHitboxOffset, 0.0f, 0.0f})
			    ->SetRotation(180.0f)
			    ->SetActive(true);
		}
		if (Game::GetInstance().Keys[GLFW_KEY_UP]) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteV"))
			    ->SetScale(glm::vec2(-16.0f, -16.0f))
			    ->SetVisible(true);
			attacking = true;
			attackDir = Direction::UP;
			attackTimeElapsed = 0.0f;
			slashHitbox
			    ->SetPosition({0.0f, -slashHitboxOffset, 0.0f})
			    ->SetRotation(270.0f)
			    ->SetActive(true);
		}
		if (Game::GetInstance().Keys[GLFW_KEY_DOWN]) {
			((SpriteSheetGameObject *)GetChild("SlashSpriteV"))
			    ->SetScale(glm::vec2(16.0f, 16.0f))
			    ->SetVisible(true);
			attacking = true;
			attackDir = Direction::DOWN;
			attackTimeElapsed = 0.0f;
			slashHitbox
			    ->SetPosition({0.0f, slashHitboxOffset, 0.0f})
			    ->SetRotation(90.0f)
			    ->SetActive(true);
		}
	}
}

void Player::LateUpdate(float deltaTime) {
	if (mHealth <= 0 && Game::GetInstance().GetState() == GameState::GAME_ACTIVE) {
		Game::GetInstance().SetState(GameState::GAME_OVER);
		((MenuTransition *)Game::GetInstance().GetActiveScene()->GetChild("MenuTransition"))->Transition([]() {
			Game::GetInstance().GetActiveScene()->GetChild("UI")->SetActive(true)->SetVisible(true);
		});
        ((Saver *)Game::GetInstance().GetActiveScene()->GetChild("Saver"))->DeleteSave();
	}

	ColliderGameObject::LateUpdate(deltaTime);
}
