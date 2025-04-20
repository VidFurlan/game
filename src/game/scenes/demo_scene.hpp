#pragma once

#include "scene_game_object.hpp"

class DemoScene : public SceneGameObject {
   public:
	DemoScene();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

   private:
	float mTime = 0.0f;
};
