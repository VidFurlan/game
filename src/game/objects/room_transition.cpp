#include "room_transition.hpp"

#include <functional>
#include <string>

#include "game.hpp"

RoomTransition::RoomTransition(std::string name, GameObject *parent) : SpriteGameObject(name, parent, "transition") {
	SetScale({Game::GetInstance().GetWindow()->GetWidth(), Game::GetInstance().GetWindow()->GetHeight()});
	SetVisible(false);
	SetZIndex(100);
}

void RoomTransition::Update(float deltaTime) {
	if (mTransitioning) {
		mTransitionTimeElapsed += deltaTime;
		bool rising = mTransitionTimeElapsed < mTransitionTime / 2;
		if (rising != mPreviousRising) {
            if (mCallback) {
                mCallback();
            }
		}
        mPreviousRising = rising;
		if (mTransitionTimeElapsed > mTransitionTime / 2) {
			mColor.a = 1.0f - (mTransitionTimeElapsed - mTransitionTime / 2) / (mTransitionTime / 2);
		} else {
			mColor.a = mTransitionTimeElapsed / (mTransitionTime / 2);
		}

		if (mTransitionTimeElapsed > mTransitionTime) {
			mTransitioning = false;
			mTransitionTimeElapsed = 0.0f;
			SetVisible(false);
			Game::GetInstance().SetState(GameState::GAME_ACTIVE);
		}
	}
}

void RoomTransition::Transition(std::function<void()> callback) {
	mTransitioning = true;
	mPreviousRising = true;
	SetVisible(true);
	mColor.a = 0.0f;
    mCallback = callback;
	Game::GetInstance().SetState(GameState::GAME_TRANSITION);
}
