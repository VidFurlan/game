#include "sprite_game_object.hpp"

#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/type_ptr.hpp"

void SpriteGameObject::Render() {
	if (!mVisible) {
		return;
	}

	AbstractImageGameObject::Render();

	Game::GetInstance().GetSpriteRenderer()->DrawSprite(mTexture, glm::make_vec2(mRenderPosition) - mRenderSize / 2.0f * GAME_SCALE_FACTOR,
														mRenderSize * GAME_SCALE_FACTOR,
														GetGlobalRotation(), mColor);
}
