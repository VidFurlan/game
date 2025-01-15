#pragma once

#include "abstract_image_game_object.hpp"
#include "glm/ext/vector_float2.hpp"

class AbstractUiGameObject : public AbstractImageGameObject {
   public:
	AbstractUiGameObject *SetScreenAnchor(glm::vec2 screenAnchor);
	glm::vec2 GetScreenAnchor() const;

   private:
	glm::vec2 mScreenAnchor = glm::vec2(0.0f);
};
