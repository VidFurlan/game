#pragma once

#include <string>

#include "drawable_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "texture.hpp"

class AbstractImageGameObject : public DrawableGameObject {
   public:
	AbstractImageGameObject(std::string name, std::string textureName, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
	AbstractImageGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
	AbstractImageGameObject(std::string name, Texture &texture, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
	AbstractImageGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));

	AbstractImageGameObject *SetScale(glm::vec2 scale);
	AbstractImageGameObject *SetScaleX(float scaleX);
	AbstractImageGameObject *SetScaleY(float scaleY);

	glm::vec2 GetScale() const;
	float GetScaleX() const;
	float GetScaleY() const;

	AbstractImageGameObject *SetColor(glm::vec4 color);
	glm::vec4 GetColor();

	AbstractImageGameObject *SetTexture(Texture &texture);
	Texture &GetTexture();

   protected:

	Texture &mTexture;
	glm::vec4 mColor;
};
