#pragma once

#include "scene_game_object.hpp"
#include "sprite_renderer.hpp"

class MainMenuScene : public SceneGameObject {
   public:
	MainMenuScene();
	~MainMenuScene();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;

   private:
    GameObject *pBackground;
};
