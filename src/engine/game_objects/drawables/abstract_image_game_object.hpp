#pragma once

#include <string>

#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "texture.hpp"

enum class ScreenAnchor {
	CAMERA,
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	CENTER_LEFT,
	CENTER,
	CENTER_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT
};

class AbstractImageGameObject : public GameObject {
   public:
	AbstractImageGameObject(std::string name, std::string textureName, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
	AbstractImageGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
	AbstractImageGameObject(std::string name, Texture &texture, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
	AbstractImageGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos = glm::vec3(), glm::vec2 scale = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));

	virtual void Render() override;

	glm::vec4 GetColor();
	Texture &GetTexture();

	AbstractImageGameObject *SetScale(glm::vec2 scale);
	AbstractImageGameObject *SetScaleX(float scaleX);
	AbstractImageGameObject *SetScaleY(float scaleY);

	glm::vec2 GetScale() const;
	float GetScaleX() const;
	float GetScaleY() const;

	AbstractImageGameObject *SetColor(glm::vec4 color);
	AbstractImageGameObject *SetTexture(Texture &texture);

	AbstractImageGameObject *SetScreenAnchor(ScreenAnchor anchor);

   protected:
	glm::vec3 mRenderPosition = glm::vec3(0.0f);
	glm::vec2 mRenderSize = glm::vec2(0.0f);

	Texture &mTexture;
	glm::vec4 mColor;
	ScreenAnchor mAnchor = ScreenAnchor::CAMERA;
};
