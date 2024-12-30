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

	switch (mRenderType) {
		case FIT: {
            float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
			Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mCameraOffset.x, mCameraOffset.y),
																glm::vec2(mTexture.Width / maxFactor * GAME_SCALE_FACTOR, mTexture.Height / maxFactor * GAME_SCALE_FACTOR),
																GetGlobalRotation(), mColor);
		} break;

		case STRETCH_TO_FIT: {
			Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mCameraOffset.x, mCameraOffset.y),
																glm::vec2(mScale.x * GAME_SCALE_FACTOR, mScale.y * GAME_SCALE_FACTOR),
																GetGlobalRotation(), mColor);
		} break;
	}
}

