#pragma once

#include "scene_game_object.hpp"

class MenuScene : public SceneGameObject {
   public:
	MenuScene();

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
    
	static std::string mPlayerName;
};
