#include "sprite_game_object.hpp"

#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

void SpriteGameObject::Render() {
	if (!mVisible) {
		return;
	}

	GameObject::Render();

	switch (mRenderType) {
		case FIT: {
			Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
																glm::vec2(mScale.x * mTexture.Width, mScale.y * mTexture.Height),
																mPos.z, mColor);
		} break;

		case STRETCH: {
			float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
			Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::vec2(mPos.x, mPos.y),
																glm::vec2(maxFactor * mScale.x, maxFactor * mScale.y),
																mPos.z, mColor);
		} break;
	}
}

