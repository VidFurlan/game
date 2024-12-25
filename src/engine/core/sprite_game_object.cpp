#include "sprite_game_object.hpp"

#include <iostream>

#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "resource_manager.hpp"

SpriteGameObject::SpriteGameObject(std::string name, std::string textureName, glm::vec2 pos)
	: GameObject(name, pos), mTexture(ResourceManager::GetInstance().GetTexture(textureName)) {
}

SpriteGameObject::SpriteGameObject(std::string name, std::string textureName, GameObject *parent, glm::vec2 pos)
	: GameObject(name, parent, pos), mTexture(ResourceManager::GetInstance().GetTexture(textureName)) {
}

SpriteGameObject::~SpriteGameObject() {
}

void SpriteGameObject::Render() {
	if (!mVisible) {
		return;
	}

	Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
														glm::vec2(mScaleX * mTexture.Width, mScaleY * mTexture.Height),
														mPos.z);
}
