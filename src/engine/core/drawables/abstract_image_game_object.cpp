#include "abstract_image_game_object.hpp"
#include <algorithm>
#include <deque>

#include "game.hpp"
#include "resource_manager.hpp"

AbstractImageGameObject::AbstractImageGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, pos, scale), mTexture(texture), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, parent, pos, scale), mTexture(texture), mColor(color) {
}

AbstractImageGameObject::~AbstractImageGameObject() {
}

void AbstractImageGameObject::Render() {
    if (!mVisible) {
        return;
    }

    GameObject::Render();

    mCameraOffset = GetGlobalPosition() * GAME_SCALE_FACTOR - Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetPosition() * GAME_SCALE_FACTOR;
    mCameraOffset.x -= mAnchor.x * mScale.x * GAME_SCALE_FACTOR;
    mCameraOffset.y -= mAnchor.y * mScale.y * GAME_SCALE_FACTOR;
    mCameraOffset.z = 0.0f;
}

SpriteRenderType AbstractImageGameObject::GetRenderType() {
	return mRenderType;
}

glm::vec3 AbstractImageGameObject::GetColor() {
	return mColor;
}

Texture &AbstractImageGameObject::GetTexture() {
	return mTexture;
}

glm::vec2 AbstractImageGameObject::GetAnchor() {
    return mAnchor;
}

AbstractImageGameObject *AbstractImageGameObject::SetRenderType(SpriteRenderType renderType) {
	mRenderType = renderType;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetColor(glm::vec3 color) {
	mColor = color;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetTexture(Texture &texture) {
	mTexture = texture;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetAnchor(glm::vec2 anchor) {
    mAnchor = glm::clamp(anchor, glm::vec2(0.0f), glm::vec2(1.0f));
    return this;
}
