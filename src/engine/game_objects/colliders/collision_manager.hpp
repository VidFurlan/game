#pragma once

#include <set>

#include "colliders/collider_game_object.hpp"
#include "singleton.hpp"

class CollisionManager : public Singleton {
   public:
	static CollisionManager &GetInstance() {
		static CollisionManager instance;
		return instance;
	}

	void Update(float deltaTime);

	void CheckAgainsAll(ColliderGameObject *obj1);
    ColliderGameObject::CollisionType CheckCollision(ColliderGameObject *obj1, ColliderGameObject *obj2);
	ColliderGameObject::CollisionType CheckAgainsAllNoCallback(ColliderGameObject *obj1);

	void AddGameObject(ColliderGameObject *gameObject);
	void RemoveGameObject(ColliderGameObject *gameObject);

   private:
	CollisionManager() = default;
	~CollisionManager() = default;

	std::set<ColliderGameObject *> mGameObjects;
};
