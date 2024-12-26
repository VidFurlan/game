#include "scene_game_object.hpp"
#include "game.hpp"

SceneGameObject::SceneGameObject(std::string name)
	: GameObject(name, glm::vec2(0.0f, 0.0f)) {
    pSpriteRenderer = Game::GetInstance().GetSpriteRenderer();
    pResourceManager = &Game::GetInstance().GetResourceManager()->GetInstance();
}

SceneGameObject::~SceneGameObject() {
    for (auto &child : children) {
        delete child.second;
    }
}
