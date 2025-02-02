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

   private:
	PhysicsManager() = default;
	~PhysicsManager() = default;

	std::set<PhysicsGameObject *> mGameObjects;
};
