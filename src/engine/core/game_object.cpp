#include "game_object.hpp"

Pos2d::Pos2d()
	: x(0), y(0), rot(0) {}
Pos2d::Pos2d(float x, float y)
	: x(x), y(y), rot(0) {}
Pos2d::Pos2d(float x, float y, float rot)
	: x(x), y(y), rot(rot) {}

Pos2d Pos2d::operator+(Pos2d pos) const {
	return Pos2d(x + pos.x, y + pos.y, rot + pos.rot);
}

Pos2d Pos2d::operator-(Pos2d pos) const {
	return Pos2d(x - pos.x, y - pos.y, rot - pos.rot);
}

Pos2d Pos2d::operator*(Pos2d pos) const {
	return Pos2d(x * pos.x, y * pos.y, rot * pos.rot);
}

Pos2d Pos2d::operator/(Pos2d pos) const {
	return Pos2d(x / pos.x, y / pos.y, rot / pos.rot);
}

Pos2d Pos2d::operator+=(Pos2d pos) {
	x += pos.x;
	y += pos.y;
	rot += pos.rot;
	return *this;
}

Pos2d Pos2d::operator-=(Pos2d pos) {
	x -= pos.x;
	y -= pos.y;
	rot -= pos.rot;
	return *this;
}

Pos2d Pos2d::operator*=(Pos2d pos) {
	x *= pos.x;
	y *= pos.y;
	rot *= pos.rot;
	return *this;
}

Pos2d Pos2d::operator/=(Pos2d pos) {
	x /= pos.x;
	y /= pos.y;
	rot /= pos.rot;
	return *this;
}

GameObject::GameObject(std::string name, Pos2d pos)
	: mName(name), mPos(pos), pParent(nullptr), mActive(true), mVisible(true), mScaleX(1), mScaleY(1) {
}

GameObject::GameObject(std::string name, GameObject *parent, Pos2d pos)
    : mName(name), mPos(pos), pParent(parent), mActive(true), mVisible(true), mScaleX(1), mScaleY(1) {
}

GameObject::~GameObject() {
	for (auto child : children) {
		delete child.second;
	}
}

void GameObject::Update() {
	for (auto child : children) {
		child.second->Update();
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

void GameObject::SetPosition(Pos2d pos) {
	this->mPos = pos;
}

void GameObject::SetRotation(float rot) {
	mPos.rot = rot;
}

void GameObject::SetRotation(Pos2d rot) {
	mPos.rot = rot.rot;
}

Pos2d GameObject::GetPosition() const {
	return mPos;
}

Pos2d GameObject::GetGlobalPosition() const {
	if (pParent) {
		return mPos + pParent->GetGlobalPosition();
	}
	return mPos;
}

float GameObject::GetRotation() const {
	return mPos.rot;
}

float GameObject::GetGlobalRotation() const {
	if (pParent) {
		return mPos.rot + pParent->GetGlobalRotation();
	}
	return mPos.rot;
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

GameObject GameObject::AddChildToLocal(GameObject *child) {
	AddChild(child);
	child->mPos -= mPos;
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

GameObject *GameObject::operator+=(Pos2d pos) {
    this->mPos += pos;
    return this;
}

GameObject *GameObject::operator-=(Pos2d pos) {
    this->mPos -= pos;
    return this;
}

GameObject *GameObject::operator*=(Pos2d pos) {
    this->mPos *= pos;
    return this;
}

GameObject *GameObject::operator/=(Pos2d pos) {
    this->mPos /= pos;
    return this;
}
