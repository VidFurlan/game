#include "menu_scene.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/player.hpp"
#include "objects/room_transition.hpp"
#include "objects/ui/button.hpp"
#include "objects/ui/player_ui.hpp"
#include "sprite_game_object.hpp"

MenuScene::MenuScene()
    : SceneGameObject("Game") {
}

void MenuScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();
    Game::GetInstance().SetState(GameState::GAME_MENU);

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

	pResourceManager->LoadTexture("assets/textures/ui/banner_play.png", true, "banner_play");
	pResourceManager->LoadTexture("assets/textures/ui/banner_quit.png", true, "banner_quit");
	pResourceManager->LoadTexture("assets/textures/ui/banner_menu.png", true, "banner_menu");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	// this->AddGameCamera(camera);
	// this->SetActiveCamera(camera);

	GameObject *ui = new GameObject("UI", this);
	Button *menuButton = new Button("PlayButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}, []() { Game::GetInstance().RequestLoadScene("Game"); }, new SpriteGameObject("Image", "banner_play", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}), ScreenAnchor::CENTER);

	Button *exitButton = new Button("ExitButton", ui, {0.0f, 20.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}, []() { Game::GetInstance().Quit(); }, new SpriteGameObject("Image", "banner_quit", {0.0f, 00.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}), ScreenAnchor::CENTER);
}

void MenuScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	SceneGameObject::Update(deltaTime);
}

void MenuScene::Render() {
	SceneGameObject::Render();
}
