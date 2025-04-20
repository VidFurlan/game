#include "game_scene.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/entities/enemy.hpp"
#include "objects/menu_transition.hpp"
#include "objects/player.hpp"
#include "objects/room_transition.hpp"
#include "objects/saver.hpp"
#include "objects/ui/button.hpp"
#include "objects/ui/player_ui.hpp"
#include "sprite_game_object.hpp"

GameScene::GameScene()
    : SceneGameObject("Game") {
}

void GameScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();
	Game::GetInstance().SetState(GameState::GAME_ACTIVE);

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

    Saver *saver = new Saver("Saver", this);

	Player *player = new Player("Player", this);
	AddChild(new PlayerUI(player));

	Dungeon *dungeon = new Dungeon("Dungeon", this);

    // dungeon->Generate(10, std::hash<std::string>()("ligma"));
    if (Saver::mShouldLoad && Saver::mReadyToLoad) {
        saver->Load();
        dungeon->Generate(Saver::mDungeonSaveData.roomCount, Saver::mDungeonSaveData.seed);
        for (int i = -Saver::mDungeonSaveData.roomCount; i < Saver::mDungeonSaveData.roomCount; i++) {
            for (int j = -Saver::mDungeonSaveData.roomCount; j < Saver::mDungeonSaveData.roomCount; j++) {
                Dungeon::RoomData roomData = Saver::mRoomSaveData[i + Saver::mDungeonSaveData.roomCount][j + Saver::mDungeonSaveData.roomCount];
                dungeon->SetRoomState(i, j, roomData.state);
            }
        }
        dungeon->EnterRoom(Saver::mDungeonSaveData.curX, Saver::mDungeonSaveData.curY);
    }
    else {
        srand(time(0));
        dungeon->Generate(10, rand());
    }

	RoomTransition *roomTransition = new RoomTransition("Transition", this);

	MenuTransition *menuTransition = new MenuTransition("MenuTransition", this);

	GameObject *ui = new GameObject("UI", this);
	ui->SetZIndex(0);
	ui->SetVisible(false);
	ui->SetActive(false);

	Button *menuButton = new Button("MenuButton", ui, {0.0f, -20.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}, [ui]() {
            if (!ui->GetActive()) return;
            Game::GetInstance().RequestLoadScene("Menu"); }, new SpriteGameObject("Image", "banner_menu", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}), ScreenAnchor::CENTER);

	Button *exitButton = new Button("ExitButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}, [ui]() {
            if (!ui->GetActive()) return;
            Game::GetInstance().Quit(); }, new SpriteGameObject("Image", "banner_quit", {0.0f, 00.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}), ScreenAnchor::CENTER);
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
