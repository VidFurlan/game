#pragma once

#include <functional>

#include "game_object.hpp"
#include "sprite_game_object.hpp"

class RoomTransition : public SpriteGameObject {
   public:
	RoomTransition(std::string name, GameObject *parent);

	void Update(float deltaTime) override;

	void Transition(std::function<void()> callback = []() {});

   private:
	bool mTransitioning = false;
	bool mPreviousRising = false;
	float mTransitionTime = 0.5f;
	float mTransitionTimeElapsed = 0.0f;

	std::function<void()> mCallback;
};
