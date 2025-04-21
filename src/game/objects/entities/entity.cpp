#include "entity.hpp"

#include "abstract_image_game_object.hpp"
#include "collider_game_object.hpp"
#include "game.hpp"
#include "polygon2d.hpp"

Entity::Entity(std::string name, GameObject *parent, EntityType type, Polygon2D *polygon, glm::vec3 position, glm::vec2 scale)
    : ColliderGameObject(name, parent, polygon, true),
      mType(type),
      mMoveSpeed(0.0f) {
    mPos = position;
    mScale = scale;
    mMaxHealth = 1;
    mHealth = mMaxHealth;
}

void Entity::Update(float deltaTime) {
	if (mImmune) {
		if (mImmunityTimeElapsed < 0.1f) {
			((AbstractImageGameObject *)GetChild("Sprite"))->SetColor({1.0f, 1.0f * (mImmunityTimeElapsed / 0.1f), 1.0f * (mImmunityTimeElapsed / 0.1f), 1.0f});
		} else {
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
        Death();
	}

	if (mHealth > mMaxHealth) {
		mHealth = mMaxHealth;
	}

	mImmune = true;
}

Entity *Entity::SetHealth(int health) {
	mHealth = health;
    return this;
}

Entity *Entity::SetMaxHealth(int maxHealth) {
	mMaxHealth = maxHealth;
    return this;
}

int Entity::GetHealth() const {
	return mHealth;
}

int Entity::GetMaxHealth() const {
	return mMaxHealth;
}

EntityType Entity::GetEntityType() const {
    return mType;
}

Entity::SaveData Entity::GetSaveData() const {
	SaveData data;
	data.type = mType;
	data.position = mPos;
	data.health = mHealth;
	return data;
}
