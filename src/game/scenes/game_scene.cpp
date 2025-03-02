#include "game_scene.hpp"

#include <cstdlib>
#include <functional>
#include <string>

#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/entities/enemy.hpp"
#include "objects/player.hpp"
#include "objects/room_transition.hpp"
#include "objects/ui/player_ui.hpp"

GameScene::GameScene()
    : SceneGameObject("Game") {
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
	pResourceManager->LoadTexture("assets/textures/character/slash/horizontal_slash_1.png", true, "horizontal_slash_1");
	pResourceManager->LoadTexture("assets/textures/character/enemy.png", true, "enemy");

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");
	pResourceManager->LoadTexture("assets/textures/enviroment/tileset.png", true, "tileset");

    pResourceManager->LoadTexture("assets/textures/engine/pixel.png", false, "transition");

	pResourceManager->LoadTexture("assets/textures/ui/hearts.png", true, "hearts");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	this->AddGameCamera(camera);
	this->SetActiveCamera(camera);

	Player *player = new Player("Player", this);
	AddChild(new PlayerUI(player));

	Dungeon *dungeon = new Dungeon("Dungeon", this);
	dungeon->Generate(10, std::hash<std::string>()("ligma"));

    RoomTransition *roomTransition = new RoomTransition("Transition", this);
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
