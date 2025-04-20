#pragma once

#include "scene_game_object.hpp"

class GameScene : public SceneGameObject {
   public:
	GameScene();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};
