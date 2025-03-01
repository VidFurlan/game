#include "collision_manager.hpp"
#include <iostream>

#include "collider_game_object.hpp"

void CollisionManager::Update(float deltaTime) {
	for (ColliderGameObject *obj1 : mGameObjects) {
		for (ColliderGameObject *obj2 : mGameObjects) {
            if (obj1 < obj2) continue;
            ColliderGameObject::CollisionType collision = CheckCollision(obj1, obj2);

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

void CollisionManager::CheckAgainsAll(ColliderGameObject *obj1) {
	ColliderGameObject::CollisionType maxCollision = ColliderGameObject::CollisionType::NONE;
	for (std::set<ColliderGameObject *>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); it++) {
		ColliderGameObject *obj2 = *it;
        ColliderGameObject::CollisionType collision = CheckCollision(obj1, obj2);

		if (collision == ColliderGameObject::CollisionType::OVERLAP) {
			obj1->OnCollision(obj2);
			obj2->OnCollision(obj1);
		} else if (collision == ColliderGameObject::CollisionType::TOUCH) {
			obj1->OnCollision(obj2);
			obj2->OnCollision(obj1);
		}
	}
}

ColliderGameObject::CollisionType CollisionManager::CheckAgainsAllNoCallback(ColliderGameObject *obj1) {
	ColliderGameObject::CollisionType maxCollision = ColliderGameObject::CollisionType::NONE;
	for (ColliderGameObject *obj2 : mGameObjects) {
		ColliderGameObject::CollisionType collision = obj1->CheckCollision(obj2);

		if (collision == ColliderGameObject::CollisionType::OVERLAP) {
			return collision;
		} else if (collision == ColliderGameObject::CollisionType::TOUCH) {
			maxCollision = ColliderGameObject::CollisionType::TOUCH;
		}
	}
	return maxCollision;
}

ColliderGameObject::CollisionType CollisionManager::CheckCollision(ColliderGameObject *obj1, ColliderGameObject *obj2) {
	if (obj1 == obj2) return ColliderGameObject::CollisionType::NONE;
	if (obj1->IsFixed() && obj2->IsFixed()) return ColliderGameObject::CollisionType::NONE;
	if (!obj1->IsSolid() && !obj2->IsSolid()) return obj1->CheckCollision(obj2);
	if (obj1->IsSolid() && obj2->IsSolid() && obj2->IsFixed()) return obj1->CheckCollisionAndResolve(obj2);
	if (obj1->IsSolid() && obj2->IsSolid()) return obj2->CheckCollisionAndResolve(obj1);
	return obj1->CheckCollision(obj2);
}

void CollisionManager::AddGameObject(ColliderGameObject *gameObject) {
	mGameObjects.insert(gameObject);
}

void CollisionManager::RemoveGameObject(ColliderGameObject *gameObject) {
	mGameObjects.erase(gameObject);
}
