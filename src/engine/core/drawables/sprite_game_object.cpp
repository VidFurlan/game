#include "sprite_game_object.hpp"

#include <iostream>

#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "resource_manager.hpp"

SpriteGameObject::SpriteGameObject(std::string name, std::string textureName, glm::vec2 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

SpriteGameObject::SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec2 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

SpriteGameObject::SpriteGameObject(std::string name, Texture &texture, glm::vec2 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, pos, scale), mTexture(texture), mColor(color) {
}

SpriteGameObject::SpriteGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec2 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, parent, pos, scale), mTexture(texture), mColor(color) {
}

SpriteGameObject::SpriteGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

SpriteGameObject::SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

SpriteGameObject::SpriteGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: GameObject(name, pos, scale), mTexture(texture), mColor(color) {
}

SpriteGameObject::~SpriteGameObject() {
}

void SpriteGameObject::Draw() {
	if (!mVisible) {
		return;
	}

	GameObject::Draw();

	switch (mRenderType) {
		case FIT: {
			Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
																glm::vec2(mScale.x * mTexture.Width, mScale.y * mTexture.Height),
																mPos.z, mColor);
		} break;

		case STRETCH: {
			float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
			Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
																glm::vec2(maxFactor * mScale.x * mTexture.Width, maxFactor * mScale.y * mTexture.Height),
																mPos.z, mColor);
		} break;
	}

	for (auto &maskTexture : mMaskTextures) {
		float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
		Game::GetInstance().GetSpriteRenderer()->DrawSpritesheet(*maskTexture.second, glm::vec2(mPos.x, mPos.y),
																 10, 10, 10,
																 glm::vec2(100.0f, 100.0f),
																 mPos.z, glm::vec3(1.0f), true);
	}
}

SpriteRenderType SpriteGameObject::GetRenderType() {
	return mRenderType;
}

glm::vec3 SpriteGameObject::GetColor() {
	return mColor;
}

Texture &SpriteGameObject::GetTexture() {
	return mTexture;
}

void SpriteGameObject::SetRenderType(SpriteRenderType renderType) {
	mRenderType = renderType;
}

void SpriteGameObject::SetColor(glm::vec3 color) {
	mColor = color;
}

void SpriteGameObject::SetTexture(Texture &texture) {
	mTexture = texture;
}

void SpriteGameObject::SetMaskTexture(std::string name, Texture &texture) {
	mMaskTextures[name] = &texture;
}

void SpriteGameObject::SetMaskTexture(std::string name, std::string textureName) {
	mMaskTextures[name] = &ResourceManager::GetInstance().GetTexture(textureName);
}
