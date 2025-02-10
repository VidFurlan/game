#include "demo_scene.hpp"

#include <iostream>

#include "camera_game_object.hpp"
#include "colliders/collider_game_object.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "shapes/polygon2d.hpp"
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
	// General Setup ===========================================================
	// =========================================================================
	mBackgroundColor = glm::vec3(0.239f, 0.145f, 0.231f);

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

	this->AddChild(new SpriteSheetGameObject("character_1", "character_red", {12, 4}, glm::vec3(0.0f), glm::vec2(10.0f)));
	ColliderGameObject *polygon1 =
	    new ColliderGameObject("polygon", this->GetChild("character_1"), new Polygon2D({glm::vec2(-10.0f, 0.0f), glm::vec2(-5.0f, 5.0f), glm::vec2(5.0f, 5.0f), glm::vec2(5.0f, -5.0f), glm::vec2(-5.0f, -5.0f)}), glm::vec3(0.0f), glm::vec2(1.0f));

	this->AddChild(new SpriteSheetGameObject("character_2", "character_blue", {12, 4}, glm::vec3(0.0f), glm::vec2(10.0f)));
	ColliderGameObject *polygon2 =
	    new ColliderGameObject("polygon", this->GetChild("character_2"), new Polygon2D({glm::vec2(-20.0f, 0.0f), glm::vec2(-10.0f, 10.0f), glm::vec2(10.0f, 10.0f), glm::vec2(10.0f, -10.0f), glm::vec2(-10.0f, -10.0f)}), glm::vec3(0.0f), glm::vec2(1.0f));
}

void DemoScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	SceneGameObject::Update(deltaTime);
	SpriteSheetGameObject *character1 = static_cast<SpriteSheetGameObject *>(this->GetChild("character_1"));
	SpriteSheetGameObject *character2 = static_cast<SpriteSheetGameObject *>(this->GetChild("character_2"));

	mTime += deltaTime;
	if (mTime > 0.1f) {
		mTime = 0.0f;
		character1->SetSpriteSheetFrame((character1->GetFrameIndex() + 1) % 4 + 4 * 3);
		character2->SetSpriteSheetFrame((character2->GetFrameIndex() + 1) % 4 + 4 * 3);
	}

	glm::vec2 movement = glm::vec2(0.0f);
	if (Game::GetInstance().Keys[GLFW_KEY_W]) movement.y -= 1.0f;
	if (Game::GetInstance().Keys[GLFW_KEY_S]) movement.y += 1.0f;
	if (Game::GetInstance().Keys[GLFW_KEY_A]) movement.x -= 1.0f;
	if (Game::GetInstance().Keys[GLFW_KEY_D]) movement.x += 1.0f;
	*((GameObject *)character1) += movement * 10.0f * deltaTime;
    GetActiveCamera()->SetPosition(character1->GetPosition());
}

void DemoScene::Render() {
	SceneGameObject::Render();

	// pSpriteRenderer->DrawSpriteWithMask(pResourceManager->GetTexture("clouds_3_3"), pResourceManager->GetTexture("mask"), glm::vec2(0.0f, 400.0f), glm::vec2(400.0f));
}
