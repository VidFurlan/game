#include "collision_manager.hpp"

#include <iostream>

#include "collider_game_object.hpp"
#include "game.hpp"

void CollisionManager::Update(float deltaTime) {
    if (Game::GetInstance().GetState() == GameState::GAME_REPLAY) {
        return;
    }
	for (auto &tagGroup : mTaggedGameObjects) {
        //std::cout << "Tag: " << tagGroup.first << " Count: " << tagGroup.second.size() << std::endl;
		for (std::set<ColliderGameObject *>::iterator it1 = tagGroup.second.begin(); it1 != tagGroup.second.end(); it1++) {
            for (std::set<ColliderGameObject *>::iterator it2 = std::next(it1); it2 != tagGroup.second.end(); it2++) {
                if (!(*it1)->GetActive() || !(*it2)->GetActive()) continue;
                ColliderGameObject *obj1 = *it1;
                ColliderGameObject *obj2 = *it2;
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
}

void CollisionManager::CheckAgainsAll(ColliderGameObject *obj1) {
	ColliderGameObject::CollisionType maxCollision = ColliderGameObject::CollisionType::NONE;
	for (std::set<ColliderGameObject *>::iterator it = mTaggedGameObjects[obj1->GetTag()].begin(); it != mTaggedGameObjects[obj1->GetTag()].end(); ++it) {
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
	for (ColliderGameObject *obj2 : mTaggedGameObjects[obj1->GetTag()]) {
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
    mTaggedGameObjects[gameObject->GetTag()].insert(gameObject);
	mGameObjects.insert(gameObject);
}

void CollisionManager::RemoveGameObject(ColliderGameObject *gameObject) {
    mTaggedGameObjects[gameObject->GetTag()].erase(gameObject);
	mGameObjects.erase(gameObject);
}
