#pragma once

#include "game_object.hpp"
#include "texture.hpp"

class SpriteGameObject : public GameObject {
   public:
	SpriteGameObject(std::string name, std::string textureName, glm::vec2 pos = glm::vec2());
	SpriteGameObject(std::string name, std::string textureName, glm::vec3 pos = glm::vec3());
	SpriteGameObject(std::string name, std::string textureName, GameObject *parent, glm::vec2 pos = glm::vec2());
    SpriteGameObject(std::string name, std::string textureName, GameObject *parent, glm::vec3 pos = glm::vec3());
	~SpriteGameObject();

	void Render();

   private:
	Texture &mTexture;
};
