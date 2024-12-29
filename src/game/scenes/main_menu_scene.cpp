#include "main_menu_scene.hpp"

#include <iostream>
#include <ostream>

#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

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

	pResourceManager->LoadTexture("assets/textures/character/character.png", true, "character");
	pResourceManager->LoadTexture("assets/textures/character/character_red.png", true, "character_red");
	pResourceManager->LoadTexture("assets/textures/character/character_blue.png", true, "character_blue");
	pResourceManager->LoadTexture("assets/textures/character/shadow.png", true, "shadow");

	GameObject *strechDemo = this->AddChild(new GameObject("strech_demo"))
        ->SetZIndex(2000);
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("main_menu_background_1", "main_menu_background_1")))
		->SetRenderType(SpriteRenderType::STRETCH)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("main_menu_background_2", "main_menu_background_2")))
		->SetRenderType(SpriteRenderType::STRETCH)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("main_menu_background_3", "main_menu_background_3")))
		->SetRenderType(SpriteRenderType::STRETCH)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("main_menu_background_4", "main_menu_background_4")))
		->SetRenderType(SpriteRenderType::STRETCH)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	GameObject *fitDemo = this->AddChild(new GameObject("fit_demo"));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("main_menu_background_1", "main_menu_background_1")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("main_menu_background_2", "main_menu_background_2")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("main_menu_background_3", "main_menu_background_3")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("main_menu_background_4", "main_menu_background_4")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));

	this->AddChild(new SpriteSheetGameObject("character_1", "character", {12, 4}, glm::vec3(500.0f, 500.0f, 0.0f), glm::vec2(10.0f, 10.0f)))
		->AddChild(new SpriteGameObject("shadow", "shadow", glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)));
	this->AddChild(new SpriteSheetGameObject("character_2", "character_red", {12, 4}, glm::vec3(700.0f, 500.0f, 0.0f), glm::vec2(10.0f, 10.0f)))
		->AddChild(new SpriteGameObject("shadow", "shadow", glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)));
	this->AddChild(new SpriteSheetGameObject("character_3", "character_blue", {12, 4}, glm::vec3(900.0f, 500.0f, 0.0f), glm::vec2(10.0f, 10.0f)))
		->AddChild(new SpriteGameObject("shadow", "shadow", glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)));
}

float timeWaited = 0.0f;
void MainMenuScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	timeWaited += deltaTime;
	if (timeWaited > 0.1f) {
		timeWaited = 0.0f;
		SpriteSheetGameObject *character = static_cast<SpriteSheetGameObject *>(this->GetChild("character_1"));
		character->SetSpriteSheetFrame((character->GetFrameIndex() + 1) % 4 + 4 * 3);
		character = static_cast<SpriteSheetGameObject *>(this->GetChild("character_2"));
		character->SetSpriteSheetFrame((character->GetFrameIndex() + 1) % 4 + 4 * 4);
		character = static_cast<SpriteSheetGameObject *>(this->GetChild("character_3"));
		character->SetSpriteSheetFrame((character->GetFrameIndex() + 1) % 4 + 4 * 5);
	}
}

void MainMenuScene::Render() {
	SceneGameObject::Render();
}
