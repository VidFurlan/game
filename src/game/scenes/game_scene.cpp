#include "game_scene.hpp"

#include <cstdlib>
#include <functional>
#include <string>

#include "collider_game_object.hpp"
#include "debug_renderer.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/entities/enemy.hpp"
#include "objects/player.hpp"
#include "objects/ui/player_ui.hpp"

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
	pResourceManager->LoadTexture("assets/textures/character/enemy.png", true, "enemy");

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");
	pResourceManager->LoadTexture("assets/textures/enviroment/tileset.png", true, "tileset");

	pResourceManager->LoadTexture("assets/textures/ui/hearts.png", true, "hearts");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	this->AddGameCamera(camera);
	this->SetActiveCamera(camera);

	Player *player = new Player("Player", this);
	AddChild(new PlayerUI(player));

    Enemy *enemy = new Enemy("Enemy", this);

	Dungeon *dungeon = new Dungeon("Dungeon", this);
	dungeon->Generate(10, std::hash<std::string>()("420"));
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
