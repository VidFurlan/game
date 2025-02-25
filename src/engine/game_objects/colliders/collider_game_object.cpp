#include "collider_game_object.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <unordered_set>
#include <utility>

#include "colliders/collider_game_object.hpp"
#include "collision_manager.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/hash.hpp"
#include "shape2d.hpp"

ColliderGameObject::ColliderGameObject(std::string name, Shape2D *shape, bool fixed, glm::vec3 pos, glm::vec2 scale) : GameObject(name, pos, scale), mShape(shape), mFixed(fixed) {
	CollisionManager::GetInstance().AddGameObject(this);
}

ColliderGameObject::ColliderGameObject(std::string name, GameObject *parent, Shape2D *shape, bool fixed, glm::vec3 pos, glm::vec2 scale) : GameObject(name, parent, pos, scale), mShape(shape), mFixed(fixed) {
	CollisionManager::GetInstance().AddGameObject(this);
}

ColliderGameObject::~ColliderGameObject() {
	CollisionManager::GetInstance().RemoveGameObject(this);
	delete mShape;
}

void ColliderGameObject::Update(float deltaTime) {
	GameObject::Update(deltaTime);
}

void ColliderGameObject::OnCollision(ColliderGameObject *other, CollisionType type) {
	if (mOnCollision) {
		mOnCollision(other, type);
	}

    mShape->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void ColliderGameObject::Render() {
	GameObject::Render();
	if (mShape != nullptr && Game::GetInstance().IsDebugMode() && mActive) {
		mGlobalPosition = GetGlobalPosition();
		mShape->DrawDebug(mGlobalPosition, mGlobalPosition.z, mScale);
		mShape->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
}

ColliderGameObject::CollisionType ColliderGameObject::CheckCollision(ColliderGameObject *other) const {
	if (mShape == nullptr || other->mShape == nullptr || !mActive || !other->mActive) {
		return CollisionType::NONE;
	}

	mShape->scale = mScale;
	other->mShape->scale = other->mScale;

	glm::vec2 pos1 = glm::vec2(GetGlobalPosition());
	glm::vec2 pos2 = glm::vec2(other->GetGlobalPosition());

	auto [collisionType, distance] = CheckShapeOverlap(mShape, other->mShape, glm::vec3(pos1, GetGlobalRotation()), glm::vec3(pos2, other->GetGlobalRotation()));

	return collisionType;
}

ColliderGameObject::CollisionType ColliderGameObject::CheckCollisionAndResolve(ColliderGameObject *other) {
	if (mShape == nullptr || other->mShape == nullptr) {
		return CollisionType::NONE;
	}

	mShape->scale = mScale;
	other->mShape->scale = other->mScale;

	glm::vec2 pos1 = glm::vec2(GetGlobalPosition());
	glm::vec2 pos2 = glm::vec2(other->GetGlobalPosition());

	auto [collisionType, collisionData] = CheckShapeOverlap(mShape, other->mShape, glm::vec3(pos1, GetGlobalRotation()), glm::vec3(pos2, other->GetGlobalRotation()));

	if (collisionType == CollisionType::OVERLAP) {
		ResolveCollision(collisionData.first, collisionData.second);
	}

	return collisionType;
}

void ColliderGameObject::ResolveCollision(float overlap, glm::vec2 minAxis) {
	mPos.x += minAxis.x * overlap;
	mPos.y += minAxis.y * overlap;
}

ColliderGameObject::CollisionType ColliderGameObject::CheckPointCollision(glm::vec2 point) const {
	if (mShape == nullptr) {
		return CollisionType::NONE;
	}

	glm::vec3 pos = GetGlobalPosition();
	pos.z = GetGlobalRotation();

	std::vector<glm::vec2> vertices = mShape->GetVertices(pos);

	bool inside = false;
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec2 p1 = vertices[i];
		glm::vec2 p2 = vertices[(i + 1) % vertices.size()];
		if ((point.y > std::min(p1.y, p2.y)) && (point.y <= std::max(p1.y, p2.y)) && (point.x <= std::max(p1.x, p2.x)) && (p1.y != p2.y)) {
			float xIntersection = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
			if (p1.x == p2.x || point.x <= xIntersection) {
				inside = !inside;
			}
		}
	}
	return inside ? CollisionType::OVERLAP : CollisionType::NONE;
}

std::pair<ColliderGameObject::CollisionType, std::pair<float, glm::vec2>> ColliderGameObject::CheckShapeOverlap(Shape2D *shape1, Shape2D *shape2, glm::vec3 pos1, glm::vec3 pos2) {
	std::vector<glm::vec2> edges1 = shape1->GetEdges(pos1);
	std::vector<glm::vec2> edges2 = shape2->GetEdges(pos2);

	std::unordered_set<glm::vec2> axes;

	for (glm::vec2 edge : edges1) {
		axes.insert(glm::normalize(glm::vec2(-edge.y, edge.x)));
	}

	for (glm::vec2 edge : edges2) {
		axes.insert(glm::normalize(glm::vec2(-edge.y, edge.x)));
	}

	CollisionType minCollision = CollisionType::OVERLAP;
	float minOverlap = INFINITY;
	glm::vec2 minAxis = glm::vec2(0.0f);

	for (glm::vec2 axis : axes) {
		std::pair<float, float> proj1 = {INFINITY, -INFINITY};
		std::pair<float, float> proj2 = {INFINITY, -INFINITY};

		for (glm::vec2 vertex : shape1->GetVertices(pos1)) {
			float projection = glm::dot(vertex, axis);
			proj1.first = std::min(proj1.first, projection);
			proj1.second = std::max(proj1.second, projection);
		}

		for (glm::vec2 vertex : shape2->GetVertices(pos2)) {
			float projection = glm::dot(vertex, axis);
			proj2.first = std::min(proj2.first, projection);
			proj2.second = std::max(proj2.second, projection);
		}

		float overlap = std::min(proj1.second, proj2.second) - std::max(proj1.first, proj2.first);

		if (overlap < minOverlap) {
			minOverlap = overlap;
			minAxis = axis;
			if (glm::dot(minAxis, glm::make_vec2(pos1 - pos2)) < 0) {
				minAxis = -minAxis;
			}
		}

		if (proj1.first == proj1.second || proj2.first == proj2.second) {
			minCollision = CollisionType::TOUCH;
		}

		if (proj1.first > proj2.second || proj2.first > proj1.second) {
			return {CollisionType::NONE, {0.0f, glm::vec2(0.0f)}};
		}
	}

	return {minCollision, {minOverlap, minAxis}};
}

bool ColliderGameObject::IsFixed() {
	return mFixed;
}

ColliderGameObject *ColliderGameObject::SetOnCollision(std::function<void(ColliderGameObject *, CollisionType)> callback) {
    mOnCollision = callback;
    return this;
}
