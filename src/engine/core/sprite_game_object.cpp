#include "sprite_game_object.hpp"

#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "resource_manager.hpp"

SpriteGameObject::SpriteGameObject(std::string name, std::string textureName, glm::vec2 pos, glm::vec2 scale)
	: GameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)) {
}

SpriteGameObject::SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec2 pos, glm::vec2 scale)
	: GameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)) {
}

SpriteGameObject::SpriteGameObject(std::string name, Texture &texture, glm::vec2 pos, glm::vec2 scale)
	: GameObject(name, pos, scale), mTexture(texture) {
}

SpriteGameObject::SpriteGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec2 pos, glm::vec2 scale)
	: GameObject(name, parent, pos, scale), mTexture(texture) {
}

SpriteGameObject::SpriteGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale)
	: GameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)) {
}

SpriteGameObject::SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale)
	: GameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)) {
}

SpriteGameObject::SpriteGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale)
	: GameObject(name, pos, scale), mTexture(texture) {
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
															mPos.z);
	} else if (mRenderType == FIT) {
		float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
		Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
															glm::vec2(maxFactor * mScale.x * mTexture.Width, maxFactor * mScale.y * mTexture.Height),
															mPos.z);
	}
}

void SpriteGameObject::SetRenderType(SpriteRenderType renderType) {
	mRenderType = renderType;
}
