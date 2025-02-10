#include "game_scene.hpp"

#include <cstdlib>
#include <string>

#include "collider_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/dungeon/dungeon_generator.hpp"
#include "objects/player.hpp"
#include "polygon2d.hpp"
#include "sprite_game_object.hpp"
#include "spritesheet_game_object.hpp"

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

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");
	pResourceManager->LoadTexture("assets/textures/enviroment/tileset.png", true, "tileset");

    pResourceManager->LoadTexture("assets/engine/textures/pixel.png", true, "pixel");
    
	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================
	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	this->AddGameCamera(camera);
	this->SetActiveCamera(camera);

	GameObject *map = new GameObject("Map", this);
    int n = 10, m = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			SpriteSheetGameObject *tile = (new SpriteSheetGameObject("Tile" + std::to_string(i) + "_" + std::to_string(j), map, "tileset", {10, 10}, {i*8, j*8, 0}, {8, 8}))
                ->SetSpriteSheetFrame(6 + i % 4 + (10 * (j % 3)));
            if (i == n-1 && j == m-1) tile->SetSpriteSheetFrame(4, 5);
            else if (i == 0 && j == m-1) tile->SetSpriteSheetFrame(4, 0);
            else if (j == m-1) tile->SetSpriteSheetFrame(4, 1 + rand() % 4);
            else if (i == 0) tile->SetSpriteSheetFrame(rand() % 4, 0);
            else if (i == n-1) tile->SetSpriteSheetFrame(rand() % 4, 5);
		}
	}

	Player *player = new Player("Player", this);

    Dungeon *dungeon = DungeonGenerator(10, 100, 100, {20, 40}).Generate();
    this->AddChild(dungeon);
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
