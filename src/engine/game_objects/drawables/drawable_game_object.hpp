#pragma once

#include "game_object.hpp"

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

class DrawableGameObject : public GameObject {
   public:
	using GameObject::GameObject;

	virtual void Render() override;

	DrawableGameObject *SetScreenAnchor(ScreenAnchor anchor);
    glm::vec3 GetRenderPosition();

   protected:
	glm::vec3 mRenderPosition = glm::vec3(0.0f);
	glm::vec2 mRenderSize = glm::vec2(0.0f);
	ScreenAnchor mAnchor = ScreenAnchor::CAMERA;
};
