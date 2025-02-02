#pragma once

#include <set>

#include "physics/physics_game_object.hpp"
#include "singleton.hpp"

class PhysicsManager : public Singleton {
   public:
	static PhysicsManager &GetInstance() {
		static PhysicsManager instance;
		return instance;
	}

	void Update(float deltaTime);

    PhysicsGameObject::CollisionType CheckAgainsAll(PhysicsGameObject *obj1);
    PhysicsGameObject::CollisionType CheckAgainsAllNoCallback(PhysicsGameObject *obj1);

    void AddGameObject(PhysicsGameObject *gameObject);
    void RemoveGameObject(PhysicsGameObject *gameObject);

   private:
	PhysicsManager() = default;
	~PhysicsManager() = default;

	std::set<PhysicsGameObject *> mGameObjects;
};
