#include "menu_transition.hpp"

#include <functional>
#include <iostream>
#include <string>

#include "game.hpp"
#include "glm/common.hpp"

MenuTransition::MenuTransition(std::string name, GameObject *parent) : SpriteGameObject(name, parent, "transition") {
	SetScale({Game::GetInstance().GetWindow()->GetWidth(), Game::GetInstance().GetWindow()->GetHeight()});
	SetVisible(false);
	SetZIndex(100);
}

void MenuTransition::Update(float deltaTime) {
	if (mTransitioning) {
		mTransitionTimeElapsed += deltaTime;
        mColor.a = mTransitionTimeElapsed / mTransitionTime * 0.5f;

		if (mTransitionTimeElapsed > mTransitionTime) {
			mTransitioning = false;
            if (mCallback) {
                mCallback();
            }
		}
	}
}

void MenuTransition::Transition(std::function<void()> callback) {
	mTransitioning = true;
	SetVisible(true);
	mColor.a = 0.0f;
    mCallback = callback;
}
