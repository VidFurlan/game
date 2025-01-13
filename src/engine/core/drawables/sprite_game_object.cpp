#include "sprite_game_object.hpp"

#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

void SpriteGameObject::Render() {
	if (!mVisible) {
		return;
	}

	AbstractImageGameObject::Render();

	Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mCameraOffset.x, mCameraOffset.y),
														mScale * GAME_SCALE_FACTOR,
														GetGlobalRotation(), mColor);
}
