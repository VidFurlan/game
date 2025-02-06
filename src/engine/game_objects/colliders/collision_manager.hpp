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

	ColliderGameObject::CollisionType CheckAgainsAll(ColliderGameObject *obj1);
	ColliderGameObject::CollisionType CheckAgainsAllNoCallback(ColliderGameObject *obj1);

	void AddGameObject(ColliderGameObject *gameObject);
	void RemoveGameObject(ColliderGameObject *gameObject);

   private:
	CollisionManager() = default;
	~CollisionManager() = default;

	std::set<ColliderGameObject *> mGameObjects;
};
