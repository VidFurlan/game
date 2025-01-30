#include "physics_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"

PhysicsGameObject::PhysicsGameObject(std::string name, Shape2D *shape, glm::vec3 pos, glm::vec2 scale)
	: GameObject(name, pos, scale), mShape(shape) {
}

PhysicsGameObject::PhysicsGameObject(std::string name, GameObject *parent, Shape2D *shape, glm::vec3 pos, glm::vec2 scale)
	: GameObject(name, parent, pos, scale), mShape(shape) {
}

PhysicsGameObject::~PhysicsGameObject() {
    delete mShape;
}

void PhysicsGameObject::Update(float deltaTime) {
    GameObject::Update(deltaTime);
    mGlobalPosition = GetGlobalPosition();
}

void PhysicsGameObject::Render() {
    GameObject::Render();
    if (mShape != nullptr && Game::GetInstance().IsDebugMode()) {
        mShape->DrawDebug(mGlobalPosition, mGlobalPosition.z);
    }
}

bool PhysicsGameObject::CheckCollision(PhysicsGameObject *other) {
    if (mShape == nullptr || other->mShape == nullptr) {
        return false;
    }

    glm::vec2 pos1 = glm::vec2(mGlobalPosition.x, mGlobalPosition.y);
    glm::vec2 pos2 = glm::vec2(other->mGlobalPosition.x, other->mGlobalPosition.y);

    return mShape->CheckOverlap(mGlobalPosition, other->mShape, other->mGlobalPosition);
}
