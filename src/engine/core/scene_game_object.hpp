#pragma once

#include <string>

#include "game_object.hpp"

class SceneGameObject : protected GameObject {
   public:
	SceneGameObject(std::string name);
    SceneGameObject(std::string name, GameObject *parent);
};
