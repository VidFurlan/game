#include "game_object.hpp"

#include <cmath>
#include <iostream>
#include <unordered_map>

#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"

GameObject::GameObject(std::string name, glm::vec3 pos, glm::vec2 scale)
    : mName(name), mPos(pos), pParent(nullptr), mActive(true), mVisible(true), mScale(scale) {
}

GameObject::GameObject(std::string name, GameObject *parent, glm::vec3 pos, glm::vec2 scale)
    : mName(name), mPos(pos), pParent(parent), mActive(true), mVisible(true), mScale(scale) {
	parent->AddChild(this);
}

GameObject::~GameObject() {
	if (pParent)
		pParent->RemoveChild(mName);
	for (auto child : children) {
		delete child.second;
	}
}

void GameObject::Update(float deltaTime) {
	for (auto child : children) {
		child.second->Update(deltaTime);
	}
}

void GameObject::Render() {
	if (!mVisible) {
		return;
	}

	for (auto &[zIndex, childrenByZIndex] : mChildrenByZIndex) {
		for (auto child : childrenByZIndex) {
			child->Render();
		}
	}
}

std::string GameObject::GetName() const {
	return mName;
}

GameObject *GameObject::SetActive(bool active) {
	this->mActive = active;
	return this;
}

bool GameObject::GetActive() const {
	return mActive;
}

GameObject *GameObject::SetVisible(bool visible) {
	this->mVisible = visible;
	return this;
}

bool GameObject::GetVisible() const {
	return mVisible;
}

GameObject *GameObject::SetPosition(glm::vec2 pos) {
	this->mPos.x = pos.x;
	this->mPos.y = pos.y;
	return this;
}

GameObject *GameObject::SetPosition(glm::vec3 pos) {
	this->mPos = pos;
	return this;
}

GameObject *GameObject::SetRotation(float rot) {
	this->mPos.z = rot;
	return this;
}

GameObject *GameObject::SetRotation(glm::vec3 rot) {
	this->mPos.z = rot.z;
	return this;
}

glm::vec3 GameObject::GetPosition() const {
	return mPos;
}

glm::vec3 GameObject::GetGlobalPosition() const {
	glm::vec2 pos(mPos.x, mPos.y);
	float rotation = mPos.z;
	const GameObject *parent = pParent;

	while (parent) {
		float parentRotation = parent->mPos.z;
		glm::vec2 parentPos(parent->mPos.x, parent->mPos.y);

		float radians = glm::radians(parentRotation);

		float cosAngle = cos(radians);
		float sinAngle = sin(radians);
		pos = glm::vec2(
		    cosAngle * pos.x - sinAngle * pos.y,
		    sinAngle * pos.x + cosAngle * pos.y);

		pos += parentPos;

		rotation += parentRotation;

		parent = parent->pParent;
	}

	return glm::vec3(pos, rotation);
}

float GameObject::GetRotation() const {
	return mPos.z;
}

float GameObject::GetGlobalRotation() const {
	float rotation = mPos.z;
	const GameObject *parent = pParent;

	while (parent) {
		rotation += parent->mPos.z;
		parent = parent->pParent;
	}

	return rotation;
}

GameObject *GameObject::SetZIndex(int zIndex) {
	if (mZIndex == zIndex) {
		return this;
	}

	if (pParent) {
		pParent->mChildrenByZIndex[mZIndex].erase(this);
		pParent->mChildrenByZIndex[zIndex].insert(this);
	}

	mZIndex = zIndex;
	return this;
}

int GameObject::GetZIndex() const {
	return mZIndex;
}

GameObject *GameObject::GetParent() const {
	return pParent;
}

GameObject *GameObject::GetChild(std::string name) const {
	if (children.find(name) == children.end()) {
		return nullptr;
	}
	return children.at(name);
}

std::unordered_map<std::string, GameObject *> *GameObject::GetChildren() const {
	return (std::unordered_map<std::string, GameObject *> *)&children;
}

unsigned int GameObject::GetChildrenCount() const {
	unsigned int count = 0;
	for (auto child : children) {
		if (child.second->GetActive()) {
			count += 1 + child.second->GetChildrenCount();
		}
	}
	return count;
}

GameObject *GameObject::AddChild(GameObject *child) {
	if (child->pParent != nullptr) {
		child->pParent->RemoveChild(child->GetName());
	}
	child->pParent = this;
	children[child->GetName()] = child;
	mChildrenByZIndex[child->GetZIndex()].insert(child);
	return child;
}

GameObject *GameObject::AddChildToLocalPos(GameObject *child) {
	glm::vec3 pos = child->GetPosition();
	GameObject *parent = this;
	while (parent) {
		pos += parent->GetPosition();
		parent = parent->pParent;
	}
	child->SetPosition(pos - GetGlobalPosition());

	AddChild(child);
	return child;
}

/**
 * @brief Remove a child from the game object but do not delete it!
 * If memory is leaking check here!
 */
GameObject *GameObject::RemoveChild(std::string name) {
	GameObject *child = children[name];
	if (child == nullptr) return child;
	children.erase(name);
	mChildrenByZIndex[child->GetZIndex()].erase(child);
	child->pParent = nullptr;
	return child;
}

void GameObject::DeleteChild(std::string name) {
	GameObject *child = children[name];
	if (child == nullptr) return;
	children.erase(name);
	mChildrenByZIndex[child->GetZIndex()].erase(child);
	delete child;
}

GameObject *GameObject::operator+=(glm::vec2 pos) {
	mPos.x += pos.x;
	mPos.y += pos.y;
	return this;
}

GameObject *GameObject::operator-=(glm::vec2 pos) {
	mPos.x -= pos.x;
	mPos.y -= pos.y;
	return this;
}

GameObject *GameObject::operator*=(glm::vec2 pos) {
	mPos.x *= pos.x;
	mPos.y *= pos.y;
	return this;
}

GameObject *GameObject::operator/=(glm::vec2 pos) {
	mPos.x /= pos.x;
	mPos.y /= pos.y;
	return this;
}

GameObject *GameObject::operator+=(glm::vec3 pos) {
	mPos += pos;
	return this;
}

GameObject *GameObject::operator-=(glm::vec3 pos) {
	mPos -= pos;
	return this;
}

GameObject *GameObject::operator*=(glm::vec3 pos) {
	mPos *= pos;
	return this;
}

GameObject *GameObject::operator/=(glm::vec3 pos) {
	mPos /= pos;
	return this;
}
