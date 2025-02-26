#pragma once

#include "collider_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float3.hpp"

class Entity : public ColliderGameObject {
   public:
    using ColliderGameObject::ColliderGameObject;
    using ColliderGameObject::Update;

    void Damage(int damage);

    void SetHealth(int health);
    void SetMaxHealth(int maxHealth);

    int GetHealth() const;
    int GetMaxHealth() const;

   private:
    int mMaxHealth;
    int mHealth;
    float mMoveSpeed;
};
