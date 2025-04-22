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
#include "objects/saver.hpp"
#include "objects/ui/button.hpp"
#include "objects/ui/player_ui.hpp"
#include "sprite_game_object.hpp"
#include "text_game_object.hpp"

std::string MenuScene::mPlayerName = "AAA";

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

	pResourceManager->LoadTexture("assets/textures/ui/banner.png", true, "banner");
	pResourceManager->LoadTexture("assets/textures/ui/banner_play.png", true, "banner_play");
	pResourceManager->LoadTexture("assets/textures/ui/banner_quit.png", true, "banner_quit");
	pResourceManager->LoadTexture("assets/textures/ui/banner_menu.png", true, "banner_menu");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	// this->AddGameCamera(camera);
	// this->SetActiveCamera(camera);

	Saver *saver = new Saver("Saver", this);
	saver->Load();

	GameObject *ui = new GameObject("UI", this);

	ui->AddChild(new TextGameObject("Text", "KUL IGRICA", TextGameObject::TextProperties("default", 300.0f, true), {0.0f, -30.0f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(0);

	for (int i = -1; i < 2; i++) {
		Button *charButton = new Button("Name" + std::to_string(i + 1), ui, {i * 6.0f, -10.0f, 0.0f}, {5.0f, 5.0f}, []() {}, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 192.0f / 2.0}));
		charButton->SetOnClick([charButton]() {
			int i = charButton->GetName().back() - '0';
			std::string name = ((MenuScene *)Game::GetInstance().GetActiveScene())->mPlayerName;
			name[i]++;
			if (name[i] > 'Z') name[i] = 'A';
			for (int j = 0; j < 3; j++) {
				((TextGameObject *)Game::GetInstance().GetActiveScene()->GetChild("UI")->GetChild("Name" + std::to_string(j))->GetChild("Text"))->SetText(std::string(1, name[j]));
			}
			((MenuScene *)Game::GetInstance().GetActiveScene())->mPlayerName = name;
		});
		charButton->GetChild("Image")->SetVisible(false);
		charButton->AddChild(new TextGameObject("Text", charButton, std::string(1, mPlayerName[i + 1]), TextGameObject::TextProperties("default", 190.0f, true), {1.0f, 0.0f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);
	}

	if (saver->mReadyToLoad) {
		Button *loadButton = new Button("LoadButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, []() { Saver::mShouldLoad = 1; Game::GetInstance().RequestLoadScene("Game"); }, new SpriteGameObject("Image", this, "banner", {0.0f, 00.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
		loadButton->SetPosition({0.0f, 5.0f, 0.0f});
		loadButton->AddChild(new TextGameObject("Text", "LOAD", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);
	}

	Button *playButton = new Button("PlayButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, []() { Player::mCatCount = Player::mKillCount = 0; Game::GetInstance().RequestLoadScene("Game"); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	playButton->SetPosition({0.0f, 20.0f, 0.0f});
	playButton->AddChild(new TextGameObject("Text", "PLAY", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);

	Button *exitButton = new Button("ExitButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, []() { Game::GetInstance().Quit(); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	exitButton->SetPosition({0.0f, 35.0f, 0.0f});
	exitButton->AddChild(new TextGameObject("Text", "EXIT", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);

	Button *leaderboardButton = new Button("LeaderboardButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, []() { Game::GetInstance().RequestLoadScene("Scoreboard"); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	leaderboardButton->SetPosition({0.0f, 50.0f, 0.0f});
	leaderboardButton->AddChild(new TextGameObject("Text", "LEADERBOARD", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);
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
