#pragma once

#include "scene_game_object.hpp"

class GameScene : public SceneGameObject {
   public:
	GameScene();
	~GameScene();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
};
