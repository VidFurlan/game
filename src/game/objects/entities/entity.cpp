#include "entity.hpp"
#include "game.hpp"

void Entity::Update(float deltaTime) {
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
	mHealth -= damage;

	if (mHealth <= 0) {
        mHealth = 0;
        mActive = false;
        mVisible = false;
	}

	if (mHealth > mMaxHealth) {
		mHealth = mMaxHealth;
	}
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
