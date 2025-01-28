#include "demo_scene.hpp"
#include <iostream>

#include "camera_game_object.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

#include "shapes/polygon2d.hpp"

DemoScene::DemoScene()
	: SceneGameObject("Demo") {
}

DemoScene::~DemoScene() {
}

void DemoScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();

	// =========================================================================
	// General Setup ===========================================================
	// =========================================================================
	mBackgroundColor = glm::vec3(0.1f, 0.1f, 0.7f);

	// =========================================================================
	// Load textures ===========================================================
	// =========================================================================
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_1/1.png", true, "clouds_1_1");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_1/2.png", true, "clouds_1_2");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_1/3.png", true, "clouds_1_3");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_1/4.png", true, "clouds_1_4");

	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_2/1.png", true, "clouds_2_1");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_2/2.png", true, "clouds_2_2");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_2/3.png", true, "clouds_2_3");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_2/4.png", true, "clouds_2_4");

	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_3/1.png", true, "clouds_3_1");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_3/2.png", true, "clouds_3_2");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_3/3.png", true, "clouds_3_3");
	pResourceManager->LoadTexture("assets/textures/backgrounds/clouds/clouds_3/4.png", true, "clouds_3_4");

	pResourceManager->LoadTexture("assets/textures/character/character.png", true, "character");
	pResourceManager->LoadTexture("assets/textures/character/character_red.png", true, "character_red");
	pResourceManager->LoadTexture("assets/textures/character/character_blue.png", true, "character_blue");
	pResourceManager->LoadTexture("assets/textures/character/shadow.png", true, "shadow");

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "background");

	pResourceManager->LoadTexture("assets/textures/masks/test.png", false, "mask");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	this->AddGameCamera(new CameraGameObject("main_camera", this))
		->SetActiveCamera("main_camera");
	this->AddGameCamera(new CameraGameObject("extra_camera", this));
    

	GameObject *imageDemos = this->AddChild(new GameObject("image_demos"))
								 ->SetPosition(glm::vec3(30.0f, 30.0f, -90.0f));

	GameObject *strechDemo = imageDemos->AddChild(new GameObject("strech_demo"))
								 ->SetZIndex(1000);

	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_1", "clouds_1_1")))
		->SetScale(glm::vec2(40.0f))
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_2", "clouds_1_2")))
		->SetScale(glm::vec2(40.0f))
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_3", "clouds_1_3")))
		->SetScale(glm::vec2(40.0f))
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_4", "clouds_1_4")))
		->SetScale(glm::vec2(40.0f))
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	GameObject *fitDemo = imageDemos->AddChild(new GameObject("fit_demo"))
							  ->SetPosition(glm::vec3(0.0f, 40.0f, 0.0f));

	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_1", "clouds_2_1")))
		->SetScale(glm::vec2(40.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_2", "clouds_2_2")))
		->SetScale(glm::vec2(40.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_3", "clouds_2_3")))
		->SetScale(glm::vec2(40.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_4", "clouds_2_4")))
		->SetScale(glm::vec2(40.0f));

	imageDemos->AddChild(new SpriteSheetGameObject("character_1", "character", {12, 4}, glm::vec3(15.0f, 75.0f, 0.0f), glm::vec2(10.0f)));
	imageDemos->AddChild(new SpriteSheetGameObject("character_2", "character_red", {12, 4}, glm::vec3(25.0f, 75.0f, 0.0f), glm::vec2(10.0f)));
	imageDemos->AddChild(new SpriteSheetGameObject("character_3", "character_blue", {12, 4}, glm::vec3(35.0f, 75.0f, 0.0f), glm::vec2(10.0f)));

	/*
	GameObject *background = this->AddChild(new GameObject("background"))
								 ->SetPosition(glm::vec3(45.0f, 5.0f, 0.0f))
								 ->SetZIndex(1001);
	for (int i = 0; i < 8; i++) {
		GameObject *row = background->AddChild(new GameObject("row_" + std::to_string(i)));
		for (int j = 0; j < 8; j++) {
			row->AddChild(new SpriteSheetGameObject("background_" + std::to_string(i) + "_" + std::to_string(j), "background", {8, 8}, glm::vec3(j * 5.0f, i * 5.0f, 0.0f), glm::vec2(5.0f, 5.0f)));
			bool cracked = rand() % 6 == 0;
			if (cracked) static_cast<SpriteSheetGameObject *>(row->GetChild("background_" + std::to_string(i) + "_" + std::to_string(j)))->SetSpriteSheetFrame({1, 0});
		}
	}
	*/

	SpriteSheetGameObject *point1 = static_cast<SpriteSheetGameObject *>(this->AddChild(new SpriteSheetGameObject("point_1", "background", {8, 8}, glm::vec3(50.0f, 50.0f, 0.0f), glm::vec2(5.0f, 5.0f))));
	point1->SetSpriteSheetFrame({7, 0});
	SpriteSheetGameObject *point2 = static_cast<SpriteSheetGameObject *>(point1->AddChild(new SpriteSheetGameObject("point_2", "background", {8, 8}, glm::vec3(15.0f, 0.0f, 65.0f), glm::vec2(5.0f, 5.0f))));
	point2->SetSpriteSheetFrame({7, 0});
	SpriteSheetGameObject *point3 = static_cast<SpriteSheetGameObject *>(point2->AddChild(new SpriteSheetGameObject("point_3", "background", {8, 8}, glm::vec3(15.0f, 0.0f, 45.0f), glm::vec2(5.0f, 5.0f))));
	point3->SetSpriteSheetFrame({7, 0});
	SpriteSheetGameObject *centerPoint = static_cast<SpriteSheetGameObject *>(this->AddChild(new SpriteSheetGameObject("point_3", "background", {8, 8}, glm::vec3(0.0f), glm::vec2(5.0f, 5.0f))));
	centerPoint->SetSpriteSheetFrame({7, 0});
    imageDemos->AddChild(centerPoint);
}

void DemoScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	mTime += deltaTime;
	if (mTime > 0.1f) {
		mTime = 0.0f;
		SpriteSheetGameObject *character = static_cast<SpriteSheetGameObject *>(this->GetChild("image_demos")->GetChild("character_1"));
		character->SetSpriteSheetFrame((character->GetFrameIndex() + 1) % 4 + 4 * 3);
		character = static_cast<SpriteSheetGameObject *>(this->GetChild("image_demos")->GetChild("character_2"));
		character->SetSpriteSheetFrame((character->GetFrameIndex() + 1) % 4 + 4 * 4);
		character = static_cast<SpriteSheetGameObject *>(this->GetChild("image_demos")->GetChild("character_3"));
		character->SetSpriteSheetFrame((character->GetFrameIndex() + 1) % 4 + 4 * 5);
	}
}

void DemoScene::Render() {
	SceneGameObject::Render();

	// pSpriteRenderer->DrawSpriteWithMask(pResourceManager->GetTexture("clouds_3_3"), pResourceManager->GetTexture("mask"), glm::vec2(0.0f, 400.0f), glm::vec2(400.0f));
}
