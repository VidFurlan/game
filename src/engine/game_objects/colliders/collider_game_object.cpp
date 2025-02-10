#include "collider_game_object.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "colliders/collider_game_object.hpp"
#include "collision_manager.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtx/hash.hpp"
#include "shape2d.hpp"

ColliderGameObject::ColliderGameObject(std::string name, Shape2D *shape, glm::vec3 pos, glm::vec2 scale) : GameObject(name, pos, scale), mShape(shape) {
	CollisionManager::GetInstance().AddGameObject(this);
}

ColliderGameObject::ColliderGameObject(std::string name, GameObject *parent, Shape2D *shape, glm::vec3 pos, glm::vec2 scale) : GameObject(name, parent, pos, scale), mShape(shape) {
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
	mShape->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

void ColliderGameObject::Render() {
	GameObject::Render();
	if (mShape != nullptr && Game::GetInstance().IsDebugMode()) {
		mGlobalPosition = GetGlobalPosition();
		mShape->DrawDebug(mGlobalPosition, mGlobalPosition.z, mScale);
	}
	mShape->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

ColliderGameObject::CollisionType ColliderGameObject::CheckCollision(ColliderGameObject *other) const {
	if (mShape == nullptr || other->mShape == nullptr) {
		return CollisionType::NONE;
	}

	glm::vec2 pos1 = glm::vec2(GetGlobalPosition());
	glm::vec2 pos2 = glm::vec2(other->GetGlobalPosition());

	return CheckShapeOverlap(mShape, other->mShape, glm::vec3(pos1, GetGlobalRotation()), glm::vec3(pos2, other->GetGlobalRotation()));
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

ColliderGameObject::CollisionType ColliderGameObject::CheckShapeOverlap(Shape2D *shape1, Shape2D *shape2, glm::vec3 pos1, glm::vec3 pos2) {
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

		if (proj1.first == proj1.second || proj2.first == proj2.second) {
			minCollision = CollisionType::TOUCH;
		}

		if (proj1.first > proj2.second || proj2.first > proj1.second) {
			return CollisionType::NONE;
		}
	}

	return minCollision;
}
