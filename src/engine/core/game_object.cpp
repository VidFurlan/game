#include "game_object.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"

GameObject::GameObject(std::string name, glm::vec2 pos)
    : mName(name), mPos(glm::make_vec3(pos)), pParent(nullptr), mActive(true), mVisible(true), mScaleX(1), mScaleY(1) {
}

GameObject::GameObject(std::string name, glm::vec3 pos)
	: mName(name), mPos(pos), pParent(nullptr), mActive(true), mVisible(true), mScaleX(1), mScaleY(1) {
}

GameObject::GameObject(std::string name, GameObject *parent, glm::vec2 pos)
    : mName(name), mPos(glm::make_vec3(pos)), pParent(parent), mActive(true), mVisible(true), mScaleX(1), mScaleY(1) {
}   

GameObject::GameObject(std::string name, GameObject *parent, glm::vec3 pos)
    : mName(name), mPos(pos), pParent(parent), mActive(true), mVisible(true), mScaleX(1), mScaleY(1) {
}

GameObject::~GameObject() {
    pParent->RemoveChild(mName);
	for (auto child : children) {
		delete child.second;
	}
}

void GameObject::Update() {
	for (auto child : children) {
		child.second->Update();
	}
}

void GameObject::Render() {
    for (auto child : children) {
        child.second->Render();
    }
}

std::string GameObject::GetName() const {
	return mName;
}

void GameObject::SetActive(bool active) {
	this->mActive = active;
}

bool GameObject::GetActive() const {
	return mActive;
}

void GameObject::SetVisible(bool visible) {
	this->mVisible = visible;
}

bool GameObject::GetVisible() const {
	return mVisible;
}

void GameObject::SetPosition(glm::vec2 pos) {
    this->mPos.x = pos.x;
    this->mPos.y = pos.y;
}

void GameObject::SetPosition(glm::vec3 pos) {
    this->mPos = pos;
}

void GameObject::SetRotation(float rot) {
    this->mPos.z = rot;
}

void GameObject::SetRotation(glm::vec3 rot) {
    this->mPos.z = rot.z;
}

glm::vec3 GameObject::GetPosition() const {
    return mPos;
}

glm::vec3 GameObject::GetGlobalPosition() const {
    glm::vec3 pos = mPos;
    GameObject *parent = pParent;
    while (parent) {
        pos += parent->mPos;
        parent = parent->pParent;
    }
    return pos;
}

float GameObject::GetRotation() const {
    return mPos.z;
}

float GameObject::GetGlobalRotation() const {
    float rot = mPos.z;
    GameObject *parent = pParent;
    while (parent) {
        rot += parent->mPos.z;
        parent = parent->pParent;
    }
    return rot;
}

void GameObject::SetScale(float scaleX, float scaleY) {
	this->mScaleX = scaleX;
	this->mScaleY = scaleY;
}

void GameObject::SetScaleX(float scaleX) {
	this->mScaleX = scaleX;
}

void GameObject::SetScaleY(float scaleY) {
	this->mScaleY = scaleY;
}

float GameObject::GetScaleX() const {
	return mScaleX;
}

float GameObject::GetScaleY() const {
	return mScaleY;
}

GameObject GameObject::GetParent() const {
	return *pParent;
}

GameObject GameObject::AddChild(GameObject *child) {
	if (child->pParent) {
		child->pParent->RemoveChild(child->GetName());
	}
	child->pParent = this;
	children[child->GetName()] = child;
	return *child;
}

GameObject GameObject::AddChildToLocalPos(GameObject *child) {
    glm::vec3 pos = child->GetPosition();
    GameObject *parent = this;
    while (parent) {
        pos += parent->GetPosition();
        parent = parent->pParent;
    }
    child->SetPosition(pos - GetGlobalPosition());

	AddChild(child);
    return *child;
}

/**
 * @brief Remove a child from the game object but do not delete it!
 * If memory is leaking check here!
 */
GameObject GameObject::RemoveChild(std::string name) {
	GameObject *child = children[name];
    if (child == nullptr) return *child;
	children.erase(name);
	child->pParent = nullptr;
	return *child;
}

void GameObject::DeleteChild(std::string name) {
	GameObject *child = children[name];
	if (child == nullptr) return;
	children.erase(name);
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
