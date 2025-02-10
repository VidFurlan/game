#include "game_scene.hpp"

#include <string>

#include "collider_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/player.hpp"
#include "polygon2d.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

GameScene::GameScene()
    : SceneGameObject("Game") {
}

GameScene::~GameScene() {
}

void GameScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();

	// =========================================================================
	// General Setup ===========================================================
	// =========================================================================
	mBackgroundColor = glm::vec3(0.1f, 0.1f, 0.1f);

	// =========================================================================
	// Load textures ===========================================================
	// =========================================================================
	pResourceManager->LoadTexture("assets/textures/character/player.png", true, "player");

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	this->AddGameCamera(camera);
	this->SetActiveCamera(camera);

	GameObject *map = new GameObject("Map", this);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			(new SpriteSheetGameObject("Tile" + std::to_string(i) + "_" + std::to_string(j), map, "atlas", {8, 8}, {0, 0, 0}, {8, 8}))
			    ->SetSpriteSheetFrame({0, 0})
			    ->SetPosition({i, j});
		}
	}

	Player *player = new Player("Player", this);
}

void GameScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	SceneGameObject::Update(deltaTime);


}

void GameScene::Render() {
	SceneGameObject::Render();
}
