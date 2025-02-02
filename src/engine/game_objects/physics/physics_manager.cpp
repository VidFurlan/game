#include "physics/physics_manager.hpp"

#include "physics/physics_game_object.hpp"

void PhysicsManager::Update(float deltaTime) {
	for (PhysicsGameObject *obj1 : mGameObjects) {
		for (PhysicsGameObject *obj2 : mGameObjects) {
			if (obj1 <= obj2) continue;
			PhysicsGameObject::CollisionType collision = obj1->CheckCollision(obj2);
			if (collision == PhysicsGameObject::CollisionType::OVERLAP) {
				obj1->OnCollision(obj2);
				obj2->OnCollision(obj1);
			} else if (collision == PhysicsGameObject::CollisionType::TOUCH) {
				obj1->OnCollision(obj2);
				obj2->OnCollision(obj1);
			}
		}
	}
}

PhysicsGameObject::CollisionType PhysicsManager::CheckAgainsAll(PhysicsGameObject *obj1) {
	PhysicsGameObject::CollisionType maxCollision = PhysicsGameObject::CollisionType::NONE;
	for (PhysicsGameObject *obj2 : mGameObjects) {
		if (obj1 == obj2) continue;
		PhysicsGameObject::CollisionType collision = obj1->CheckCollision(obj2);
		if (collision != PhysicsGameObject::CollisionType::NONE) {
			obj1->OnCollision(obj2, collision);
			obj2->OnCollision(obj1, collision);
		}

		if (collision == PhysicsGameObject::CollisionType::OVERLAP) {
			return collision;
		} else if (collision == PhysicsGameObject::CollisionType::TOUCH) {
			maxCollision = PhysicsGameObject::CollisionType::TOUCH;
		}
	}
	return maxCollision;
}

PhysicsGameObject::CollisionType PhysicsManager::CheckAgainsAllNoCallback(PhysicsGameObject *obj1) {
	PhysicsGameObject::CollisionType maxCollision = PhysicsGameObject::CollisionType::NONE;
	for (PhysicsGameObject *obj2 : mGameObjects) {
		if (obj1 == obj2) continue;
		PhysicsGameObject::CollisionType collision = obj1->CheckCollision(obj2);

		if (collision == PhysicsGameObject::CollisionType::OVERLAP) {
			return collision;
		} else if (collision == PhysicsGameObject::CollisionType::TOUCH) {
			maxCollision = PhysicsGameObject::CollisionType::TOUCH;
		}
	}
	return maxCollision;
}

void PhysicsManager::AddGameObject(PhysicsGameObject *gameObject) {
	mGameObjects.insert(gameObject);
}

void PhysicsManager::RemoveGameObject(PhysicsGameObject *gameObject) {
	mGameObjects.erase(gameObject);
}
