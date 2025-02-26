#include "entity.hpp"

void Entity::Damage(int damage) {
	mHealth -= damage;

	if (mHealth <= 0) {
		mHealth = 0;
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
