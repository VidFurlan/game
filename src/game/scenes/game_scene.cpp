#include "game_scene.hpp"

#include <cstdlib>
#include <string>

#include "collider_game_object.hpp"
#include "debug_renderer.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
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
	mBackgroundColor = glm::vec3(0.145f, 0.075f, 0.102f);

	// =========================================================================
	// Load textures ===========================================================
	// =========================================================================
	pResourceManager->LoadTexture("assets/textures/character/player.png", true, "player");

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");
	pResourceManager->LoadTexture("assets/textures/enviroment/tileset.png", true, "tileset");

	pResourceManager->LoadTexture("assets/engine/textures/pixel.png", true, "pixel");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	this->AddGameCamera(camera);
	this->SetActiveCamera(camera);

	GameObject *map = new GameObject("Map", this);

	Player *player = new Player("Player", this);

	Dungeon *dungeon = new Dungeon("Dungeon", this);
	dungeon->Generate(10, 0);

	this->AddChild(dungeon);
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
