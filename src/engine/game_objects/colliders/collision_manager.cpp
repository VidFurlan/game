#include "collision_manager.hpp"

#include "collider_game_object.hpp"

void CollisionManager::Update(float deltaTime) {
	for (ColliderGameObject *obj1 : mGameObjects) {
		for (ColliderGameObject *obj2 : mGameObjects) {
			if (obj1 <= obj2) continue;
			ColliderGameObject::CollisionType collision = obj1->CheckCollision(obj2);
			if (collision == ColliderGameObject::CollisionType::OVERLAP) {
				obj1->OnCollision(obj2);
				obj2->OnCollision(obj1);
			} else if (collision == ColliderGameObject::CollisionType::TOUCH) {
				obj1->OnCollision(obj2);
				obj2->OnCollision(obj1);
			}
		}
	}
}

ColliderGameObject::CollisionType CollisionManager::CheckAgainsAll(ColliderGameObject *obj1) {
	ColliderGameObject::CollisionType maxCollision = ColliderGameObject::CollisionType::NONE;
	for (ColliderGameObject *obj2 : mGameObjects) {
		if (obj1 == obj2) continue;
		ColliderGameObject::CollisionType collision = obj1->CheckCollision(obj2);
		if (collision != ColliderGameObject::CollisionType::NONE) {
			obj1->OnCollision(obj2, collision);
			obj2->OnCollision(obj1, collision);
		}

		if (collision == ColliderGameObject::CollisionType::OVERLAP) {
			return collision;
		} else if (collision == ColliderGameObject::CollisionType::TOUCH) {
			maxCollision = ColliderGameObject::CollisionType::TOUCH;
		}
	}
	return maxCollision;
}

ColliderGameObject::CollisionType CollisionManager::CheckAgainsAllNoCallback(ColliderGameObject *obj1) {
	ColliderGameObject::CollisionType maxCollision = ColliderGameObject::CollisionType::NONE;
	for (ColliderGameObject *obj2 : mGameObjects) {
		if (obj1 == obj2) continue;
		ColliderGameObject::CollisionType collision = obj1->CheckCollision(obj2);

		if (collision == ColliderGameObject::CollisionType::OVERLAP) {
			return collision;
		} else if (collision == ColliderGameObject::CollisionType::TOUCH) {
			maxCollision = ColliderGameObject::CollisionType::TOUCH;
		}
	}
	return maxCollision;
}

void CollisionManager::AddGameObject(ColliderGameObject *gameObject) {
	mGameObjects.insert(gameObject);
}

void CollisionManager::RemoveGameObject(ColliderGameObject *gameObject) {
	mGameObjects.erase(gameObject);
}
