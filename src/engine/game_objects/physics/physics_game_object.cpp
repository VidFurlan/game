#include "physics_game_object.hpp"

#include <iostream>
#include <unordered_set>

#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtx/hash.hpp"

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
}

void PhysicsGameObject::OnCollision(PhysicsGameObject *other) {
    mShape->color = glm::vec3(1.0f, 0.0f, 0.0f);
}

void PhysicsGameObject::Render() {
	GameObject::Render();
	if (mShape != nullptr && Game::GetInstance().IsDebugMode()) {
		mGlobalPosition = GetGlobalPosition();
		mShape->DrawDebug(mGlobalPosition, mGlobalPosition.z, mScale);
	}
}

bool PhysicsGameObject::CheckCollision(PhysicsGameObject *other) const {
	if (mShape == nullptr || other->mShape == nullptr) {
		return false;
	}

	glm::vec2 pos1 = glm::vec2(mGlobalPosition.x, mGlobalPosition.y);
	glm::vec2 pos2 = glm::vec2(other->mGlobalPosition.x, other->mGlobalPosition.y);

	return mShape->CheckOverlap(mGlobalPosition, other->mShape, other->mGlobalPosition);
}
