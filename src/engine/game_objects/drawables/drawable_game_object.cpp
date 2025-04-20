#include "drawable_game_object.hpp"
#include "game.hpp"

void DrawableGameObject::Render() {
	if (!mVisible) {
		return;
	}

	mRenderPosition = GetGlobalPosition() * GAME_SCALE_FACTOR;
	mRenderPosition.z = 0.0f;
	mRenderSize = mScale;

    if (GetParent() != Game::GetInstance().GetActiveScene()) {
        mAnchor = ScreenAnchor::CAMERA;
    }

	switch (mAnchor) {
		case ScreenAnchor::CAMERA: {
			mRenderPosition -= Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetPosition() * GAME_SCALE_FACTOR;
			float zoom = Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetZoom();
			mRenderSize *= zoom;
			mRenderPosition *= zoom;

			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth() / 2.0f;
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight() / 2.0f;
		} break;
		case ScreenAnchor::TOP_LEFT: {
			mRenderPosition.x += 0.0f;
			mRenderPosition.y += 0.0f;
		} break;
		case ScreenAnchor::TOP_CENTER: {
			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth() / 2.0f;
			mRenderPosition.y += 0.0f;
		} break;
		case ScreenAnchor::TOP_RIGHT: {
			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth();
			mRenderPosition.y += 0.0f;
		} break;
		case ScreenAnchor::CENTER_LEFT: {
			mRenderPosition.x += 0.0f;
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight() / 2.0f;
		} break;
		case ScreenAnchor::CENTER: {
			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth() / 2.0f;
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight() / 2.0f;
		} break;
		case ScreenAnchor::CENTER_RIGHT: {
			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth();
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight() / 2.0f;
		} break;
		case ScreenAnchor::BOTTOM_LEFT: {
			mRenderPosition.x += 0.0f;
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight();
		} break;
		case ScreenAnchor::BOTTOM_CENTER: {
			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth() / 2.0f;
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight();
		} break;
		case ScreenAnchor::BOTTOM_RIGHT: {
			mRenderPosition.x += Game::GetInstance().GetWindow()->GetWidth();
			mRenderPosition.y += Game::GetInstance().GetWindow()->GetHeight();
		} break;
	}

	GameObject::Render();
}

DrawableGameObject *DrawableGameObject::SetScreenAnchor(ScreenAnchor origin) {
	mAnchor = origin;
	return this;
}

glm::vec3 DrawableGameObject::GetRenderPosition() {
    return mRenderPosition;
}
