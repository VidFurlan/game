#pragma once

#include "collider_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float3.hpp"

enum EntityType {
	TREASURE_CHEST,
	GRAY_BLOB,
};

class Entity : public ColliderGameObject {
   public:
	using ColliderGameObject::ColliderGameObject;
	
    virtual void Update(float deltaTime) override;
    virtual void LateUpdate(float deltaTime) override;

	void Damage(int damage);

	void SetHealth(int health);
	void SetMaxHealth(int maxHealth);

	int GetHealth() const;
	int GetMaxHealth() const;

   protected:
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

	int mMaxHealth = 1;
	int mHealth = mMaxHealth;
	float mMoveSpeed;
};
