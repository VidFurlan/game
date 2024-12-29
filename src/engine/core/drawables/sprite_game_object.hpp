#pragma once

#include "abstract_image_game_object.hpp"

class SpriteGameObject : public AbstractImageGameObject {
   public:
	using AbstractImageGameObject::AbstractImageGameObject;
	void Render() override;
};
