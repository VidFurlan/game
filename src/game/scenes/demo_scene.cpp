#include "demo_scene.hpp"

#include <iostream>
#include <ostream>

#include "camera_game_object.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

DemoScene::DemoScene()
	: SceneGameObject("Demo") {
}

DemoScene::~DemoScene() {
}

void DemoScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();

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
    this->AddGameCamera(new CameraGameObject("main_camera", this, glm::vec3(0.0f, 0.0f, 1.0f)))
        ->SetActiveCamera("main_camera");

	GameObject *imageDemos = this->AddChild(new GameObject("image_demos"));

	GameObject *strechDemo = imageDemos->AddChild(new GameObject("strech_demo"))->SetZIndex(2000);
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_1", "clouds_1_1")))
		->SetRenderType(SpriteRenderType::STRETCH_TO_FIT)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_2", "clouds_1_2")))
		->SetRenderType(SpriteRenderType::STRETCH_TO_FIT)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_3", "clouds_1_3")))
		->SetRenderType(SpriteRenderType::STRETCH_TO_FIT)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(strechDemo->AddChild(new SpriteGameObject("clouds_1_4", "clouds_1_4")))
		->SetRenderType(SpriteRenderType::STRETCH_TO_FIT)
		->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	GameObject *fitDemo = imageDemos->AddChild(new GameObject("fit_demo"));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_1", "clouds_2_1")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_2", "clouds_2_2")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_3", "clouds_2_3")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));
	static_cast<SpriteGameObject *>(fitDemo->AddChild(new SpriteGameObject("clouds_2_4", "clouds_2_4")))
		->SetRenderType(SpriteRenderType::FIT)
		->SetPosition(glm::vec3(600.0f, 0.0f, 0.0f));

	static_cast<SpriteSheetGameObject *>(imageDemos->AddChild(new SpriteSheetGameObject("character_1", "character", {12, 4}, glm::vec3(450.0f, 500.0f, 0.0f), glm::vec2(1.0f, 1.0f))))
        ->SetRenderType(SpriteRenderType::STRETCH_TO_FIT);

	static_cast<SpriteSheetGameObject *>(imageDemos->AddChild(new SpriteSheetGameObject("character_2", "character_red", {12, 4}, glm::vec3(500.0f, 500.0f, 0.0f), glm::vec2(1.0f, 1.0f))))
        ->SetRenderType(SpriteRenderType::FIT);

	static_cast<SpriteSheetGameObject *>(imageDemos->AddChild(new SpriteSheetGameObject("character_3", "character_blue", {12, 4}, glm::vec3(550.0f, 500.0f, 0.0f), glm::vec2(1.0f, 1.0f))))
        ->SetRenderType(SpriteRenderType::STRETCH_TO_FIT);

	//imageDemos->SetVisible(false);
    //
	//GameObject *background = this->AddChild(new GameObject("background"));
	//for (int i = 0; i < 6; i++) {
	//	GameObject *row = background->AddChild(new GameObject("row_" + std::to_string(i)));
	//	for (int j = 0; j < 6; j++) {
	//		row->AddChild(new SpriteSheetGameObject("background_" + std::to_string(i) + "_" + std::to_string(j), "background", {8, 8}, glm::vec3(j * 160.0f, i * 160.0f, 0.0f), glm::vec2(10.0f, 10.0f)));
    //        if (i == j) static_cast<SpriteSheetGameObject *>(row->GetChild("background_" + std::to_string(i) + "_" + std::to_string(j)))->SetRenderType(SpriteRenderType::STRETCH_TO_FIT);
    //        bool cracked = rand() % 6 == 0;
    //        if (cracked) static_cast<SpriteSheetGameObject *>(row->GetChild("background_" + std::to_string(i) + "_" + std::to_string(j)))->SetSpriteSheetFrame({1, 0});
	//	}
	//}
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

	pSpriteRenderer->DrawSpriteWithMask(pResourceManager->GetTexture("clouds_3_3"), pResourceManager->GetTexture("mask"), glm::vec2(600.0f, 400.0f), glm::vec2(400.0f));
}
