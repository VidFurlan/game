#pragma once

#include <string>

#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "texture.hpp"

class AbstractImageGameObject : public GameObject {
   public:
	AbstractImageGameObject(std::string name, std::string textureName, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(10.0f), glm::vec3 color = glm::vec3(1.0f));
	AbstractImageGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale = glm::vec2(10.0f), glm::vec3 color = glm::vec3(1.0f));
	AbstractImageGameObject(std::string name, Texture &texture, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(10.0f), glm::vec3 color = glm::vec3(1.0f));
	AbstractImageGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(10.0f), glm::vec3 color = glm::vec3(1.0f));

	AbstractImageGameObject(std::string name, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f)) = delete;
	AbstractImageGameObject(std::string name, GameObject *parent, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f)) = delete;

	~AbstractImageGameObject();

	virtual void Render() override;

	glm::vec3 GetColor();
	Texture &GetTexture();

	AbstractImageGameObject *SetScale(glm::vec2 scale);
	AbstractImageGameObject *SetScaleX(float scaleX);
	AbstractImageGameObject *SetScaleY(float scaleY);

	glm::vec2 GetScale() const;
	float GetScaleX() const;
	float GetScaleY() const;

	AbstractImageGameObject *SetColor(glm::vec3 color);
	AbstractImageGameObject *SetTexture(Texture &texture);

   protected:
	glm::vec3 mRenderPosition = glm::vec3(0.0f);
	glm::vec2 mRenderSize = glm::vec2(0.0f);

	Texture &mTexture;
	glm::vec3 mColor;
};
