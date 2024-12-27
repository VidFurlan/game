#pragma once

#include "game_object.hpp"
#include "glm/ext/vector_float3.hpp"
#include "texture.hpp"

enum SpriteRenderType {
	FIT,
	STRETCH
};

class SpriteGameObject : public GameObject {
   public:
    SpriteGameObject(std::string name, glm::vec3 color = glm::vec3(1.0f), glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
	SpriteGameObject(std::string name, std::string textureName, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, Texture &texture, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec2 pos = glm::vec2(), glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f, 1.0f), glm::vec3 color = glm::vec3(1.0f));
	~SpriteGameObject();

	void Render();

	void SetRenderType(SpriteRenderType);
    void SetColor(glm::vec3 color);
    void SetTexture(Texture &texture);

   private:
	Texture &mTexture;
    glm::vec3 mColor;
	SpriteRenderType mRenderType = STRETCH;
};
