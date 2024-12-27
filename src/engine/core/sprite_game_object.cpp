#include "sprite_game_object.hpp"

#include "game.hpp"
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

void SpriteGameObject::Render() {
	if (!mVisible) {
		return;
	}

	if (mRenderType == STRETCH) {
		Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
															glm::vec2(mScale.x * mTexture.Width, mScale.y * mTexture.Height),
															mPos.z, mColor);
	} else if (mRenderType == FIT) {
		float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
		Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
															glm::vec2(maxFactor * mScale.x * mTexture.Width, maxFactor * mScale.y * mTexture.Height),
															mPos.z, mColor);
	}
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
