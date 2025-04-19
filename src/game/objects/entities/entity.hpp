#pragma once

#include "collider_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float3.hpp"
#include "polygon2d.hpp"

enum EntityType {
    ENTITY,
    PLAYER,
	TREASURE_CHEST,
	GRAY_BLOB,
};

class Entity : public ColliderGameObject {
   public:
    struct SaveData {
        EntityType type;
        glm::vec2 position;
        int health;
    };

    Entity(std::string name, GameObject *parent, EntityType type, Polygon2D *polygon,
           glm::vec3 position = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));

    virtual void Update(float deltaTime) override;
    virtual void LateUpdate(float deltaTime) override;

	void Damage(int damage);

	void SetHealth(int health);
	void SetMaxHealth(int maxHealth);

	int GetHealth() const;
	int GetMaxHealth() const;

    SaveData GetSaveData() const;

   protected:
    EntityType mType;

    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    bool mImmune = false;
    float mImmunityTime = 0.0f;
    float mImmunityTimeElapsed = 0.0f;

	int mMaxHealth = 1;
	int mHealth = mMaxHealth;
	float mMoveSpeed;
};
