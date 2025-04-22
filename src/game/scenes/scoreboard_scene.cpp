#include "scoreboard_scene.hpp"

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <ios>
#include <iostream>
#include <numeric>
#include <string>

#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/saver.hpp"
#include "objects/ui/button.hpp"
#include "sprite_game_object.hpp"
#include "text_game_object.hpp"

ScoreboardScene::ScoreboardScene()
    : SceneGameObject("Game") {
}

void ScoreboardScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();
	Game::GetInstance().SetState(GameState::GAME_MENU);

	// =========================================================================
	// General Setup ===========================================================
	// =========================================================================
	mBackgroundColor = glm::vec3(0.145f, 0.075f, 0.102f);

	// =========================================================================
	// Load textures ===========================================================
	// =========================================================================

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");
	pResourceManager->LoadTexture("assets/textures/enviroment/tileset.png", true, "tileset");

	pResourceManager->LoadTexture("assets/textures/engine/pixel.png", false, "transition");

	pResourceManager->LoadTexture("assets/textures/ui/banner.png", true, "banner");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	// this->AddGameCamera(camera);
	// this->SetActiveCamera(camera);

	Saver *saver = new Saver("Saver", this);
	saver->Load();

	GameObject *ui = new GameObject("UI", this);

	ui->AddChild(new TextGameObject("Text", "LEADERBOARD", TextGameObject::TextProperties("default", 300.0f, true), {0.0f, -30.0f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(0);

    auto highscoreData = Saver::LoadHighscore();
    int idx = 0;
    for (auto &[score, name] : highscoreData) {
        name.resize(10, ' ');
        std::string text = std::to_string(idx + 1) + ". " + name + "  " + std::to_string(score);
        std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) { return std::toupper(c); });
        ui->AddChild(new TextGameObject("Text" + std::to_string(idx), this, text, TextGameObject::TextProperties("default", 150.0f, true), {0.0f, -15.0f + idx * 10.0f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(0);
        idx++;
    }

    Button *leaderboardButton = new Button("LeaderboardButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, []() { Game::GetInstance().RequestLoadScene("Menu"); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	leaderboardButton->SetPosition({0.0f, 40.0f, 0.0f});
	leaderboardButton->AddChild(new TextGameObject("Text", "BACK", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);
}

void ScoreboardScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	SceneGameObject::Update(deltaTime);
}

void ScoreboardScene::Render() {
	SceneGameObject::Render();
}
