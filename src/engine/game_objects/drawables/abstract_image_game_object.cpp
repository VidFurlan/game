#include "abstract_image_game_object.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>

#include "game.hpp"
#include "glm/common.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float2.hpp"
#include "resource_manager.hpp"

AbstractImageGameObject::AbstractImageGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : GameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : GameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : GameObject(name, pos, scale), mTexture(texture), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : GameObject(name, parent, pos, scale), mTexture(texture), mColor(color) {
}

AbstractImageGameObject::~AbstractImageGameObject() {
}

void AbstractImageGameObject::Render() {
	mRenderPosition = GetGlobalPosition() * GAME_SCALE_FACTOR - Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetPosition() * GAME_SCALE_FACTOR;
	mRenderPosition.z = 0.0f;

	float zoom = Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetZoom();
	mRenderSize = mScale * zoom;

	// Zoom origial position
	mRenderPosition *= zoom;
	// Set camera offset
	mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth() / 2.0f;
	mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight() / 2.0f;

	float maxDist = GAME_SCALE_FACTOR * std::max(glm::abs(mRenderSize.x), glm::abs(mRenderSize.y));

	if (mRenderPosition.x + maxDist < 0 || mRenderPosition.x - maxDist > Game::GetInstance().GetWindow()->GetWidth() ||
	    mRenderPosition.y + maxDist < 0 || mRenderPosition.y - maxDist > Game::GetInstance().GetWindow()->GetHeight()) {
		mVisible = false;
	} else {
		mVisible = true;
	}

	if (!mVisible) {
		return;
	}

	GameObject::Render();
}

glm::vec4 AbstractImageGameObject::GetColor() {
	return mColor;
}

Texture &AbstractImageGameObject::GetTexture() {
	return mTexture;
}

AbstractImageGameObject *AbstractImageGameObject::SetColor(glm::vec4 color) {
	mColor = color;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetTexture(Texture &texture) {
	mTexture = texture;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetScale(glm::vec2 scale) {
	mScale = scale;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetScaleX(float scaleX) {
	mScale.x = scaleX;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetScaleY(float scaleY) {
	mScale.y = scaleY;
	return this;
}

glm::vec2 AbstractImageGameObject::GetScale() const {
	return mScale;
}

float AbstractImageGameObject::GetScaleX() const {
	return mScale.x;
}

float AbstractImageGameObject::GetScaleY() const {
	return mScale.y;
}
