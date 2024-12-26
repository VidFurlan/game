#include "main_menu_scene.hpp"

#include <iostream>

#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "sprite_game_object.hpp"

MainMenuScene::MainMenuScene()
	: SceneGameObject("MainMenu") {
}

MainMenuScene::~MainMenuScene() {
}

void MainMenuScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();
	pResourceManager->LoadTexture("assets/textures/main_menu/background/1.png", true, "main_menu_background_1");
	pResourceManager->LoadTexture("assets/textures/main_menu/background/2.png", true, "main_menu_background_2");
	pResourceManager->LoadTexture("assets/textures/main_menu/background/3.png", true, "main_menu_background_3");
	pResourceManager->LoadTexture("assets/textures/main_menu/background/4.png", true, "main_menu_background_4");

	pBackground = new GameObject("main_menu_background", this);
	pBackground->AddChild(new SpriteGameObject("main_menu_background_1", "main_menu_background_1", glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 3.0f)));
	pBackground->AddChild(new SpriteGameObject("main_menu_background_2", "main_menu_background_2", glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 3.0f)));
	pBackground->AddChild(new SpriteGameObject("main_menu_background_3", "main_menu_background_3", glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 3.0f)));
	pBackground->AddChild(new SpriteGameObject("main_menu_background_4", "main_menu_background_4", glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 3.0f)));
}

void MainMenuScene::Update(float deltaTime) {
}

void MainMenuScene::Render() {
	pBackground->Render();
}
