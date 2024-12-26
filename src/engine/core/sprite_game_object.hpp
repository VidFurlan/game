#pragma once

#include "game_object.hpp"
#include "texture.hpp"

enum SpriteRenderType {
	FIT,
	STRETCH
};

class SpriteGameObject : public GameObject {
   public:
	SpriteGameObject(std::string name, std::string textureName, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, Texture &texture, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	~SpriteGameObject();

	void Render();

	void SetRenderType(SpriteRenderType);

   private:
	Texture &mTexture;
	SpriteRenderType mRenderType = STRETCH;
};
