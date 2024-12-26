#pragma once

#include <string>

#include "game_object.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

class SceneGameObject : public GameObject {
   public:
	SceneGameObject(std::string name);
	virtual ~SceneGameObject();

	virtual void Init() = 0;

   protected:
	SpriteRenderer *pSpriteRenderer = nullptr;
    ResourceManager *pResourceManager = nullptr;
};
