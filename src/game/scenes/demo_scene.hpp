#pragma once

#include "scene_game_object.hpp"

class DemoScene : public SceneGameObject {
   public:
	DemoScene();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;

   private:
	float mTime = 0.0f;
};
