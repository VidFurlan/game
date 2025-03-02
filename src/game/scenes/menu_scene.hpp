#pragma once

#include "scene_game_object.hpp"

class MenuScene : public SceneGameObject {
   public:
	MenuScene();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
};
