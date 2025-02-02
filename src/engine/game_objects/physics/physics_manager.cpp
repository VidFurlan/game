#include "physics/physics_manager.hpp"
#include "physics/physics_game_object.hpp"

void PhysicsManager::Update(float deltaTime) {
    for (PhysicsGameObject *obj1 : mGameObjects) {
        for (PhysicsGameObject *obj2 : mGameObjects) {
            if (obj1 <= obj2) continue;
            bool collision = obj1->CheckCollision(obj2);
            if (collision) {
                obj1->OnCollision(obj2);
                obj2->OnCollision(obj1);
            }
        }
    }
}
