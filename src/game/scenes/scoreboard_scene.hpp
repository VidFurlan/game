#pragma once

#include "scene_game_object.hpp"

class ScoreboardScene : public SceneGameObject {
   public:
	ScoreboardScene();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};
