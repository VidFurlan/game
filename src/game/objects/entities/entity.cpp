#include "entity.hpp"

#include "abstract_image_game_object.hpp"
#include "game.hpp"

void Entity::Update(float deltaTime) {
	if (mImmune) {
        if (mImmunityTimeElapsed < 0.1f) {
            ((AbstractImageGameObject *)GetChild("Sprite"))->SetColor({1.0f, 1.0f * (mImmunityTimeElapsed / 0.1f), 1.0f * (mImmunityTimeElapsed / 0.1f), 1.0f});
        }
        else {
            ((AbstractImageGameObject *)GetChild("Sprite"))->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
        }
		mImmunityTimeElapsed += deltaTime;
		if (mImmunityTimeElapsed > mImmunityTime) {
			mImmune = false;
			mImmunityTimeElapsed = 0.0f;
		}
	}

	mActive = Game::GetInstance().GetState() == GameState::GAME_ACTIVE;

	ColliderGameObject::Update(deltaTime);
}

void Entity::LateUpdate(float deltaTime) {
	if (mHealth <= 0) {
		SafeDelete();
	}

	ColliderGameObject::LateUpdate(deltaTime);
}

void Entity::Damage(int damage) {
	if (mImmune) {
		return;
	}

	mHealth -= damage;

	if (mHealth <= 0) {
		mHealth = 0;
		mActive = false;
		mVisible = false;
	}

	if (mHealth > mMaxHealth) {
		mHealth = mMaxHealth;
	}

	mImmune = true;
}

void Entity::SetHealth(int health) {
	mHealth = health;
}

void Entity::SetMaxHealth(int maxHealth) {
	mMaxHealth = maxHealth;
}

int Entity::GetHealth() const {
	return mHealth;
}

int Entity::GetMaxHealth() const {
	return mMaxHealth;
}
