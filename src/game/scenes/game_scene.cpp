#include "game_scene.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#include "GLFW/glfw3.h"
#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "objects/dungeon/dungeon.hpp"
#include "objects/dungeon/dungeon_room.hpp"
#include "objects/entities/enemy.hpp"
#include "objects/menu_transition.hpp"
#include "objects/player.hpp"
#include "objects/replay_manager.hpp"
#include "objects/room_transition.hpp"
#include "objects/saver.hpp"
#include "objects/ui/button.hpp"
#include "objects/ui/player_ui.hpp"
#include "sprite_game_object.hpp"
#include "text_game_object.hpp"

GameScene::GameScene()
    : SceneGameObject("Game") {
}

void GameScene::Init() {
	pResourceManager = Game::GetInstance().GetResourceManager();
	Game::GetInstance().SetState(GameState::GAME_ACTIVE);
    Player::mLevelCleared = false;

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
	pResourceManager->LoadTexture("assets/textures/character/cat.png", true, "cat");

	pResourceManager->LoadTexture("assets/textures/enviroment/spritesheet.png", true, "atlas");
	pResourceManager->LoadTexture("assets/textures/enviroment/tileset.png", true, "tileset");
	pResourceManager->LoadTexture("assets/textures/enviroment/ice.png", true, "ice");

	pResourceManager->LoadTexture("assets/textures/engine/pixel.png", false, "transition");

	pResourceManager->LoadTexture("assets/textures/ui/hearts.png", true, "hearts");

	pResourceManager->LoadTexture("assets/textures/ui/banner_play.png", true, "banner_play");
	pResourceManager->LoadTexture("assets/textures/ui/banner_quit.png", true, "banner_quit");
	pResourceManager->LoadTexture("assets/textures/ui/banner_menu.png", true, "banner_menu");

	// =========================================================================
	// Create game objects =====================================================
	// =========================================================================

	Game::GetInstance().AddOnPressKeyCallback(GLFW_KEY_ESCAPE, "OpenPauseMenu", []() {
        if (Game::GetInstance().GetState() == GameState::GAME_REPLAY) return;
		Game::GetInstance().SetState(GameState::GAME_PAUSED);
		((MenuTransition *)Game::GetInstance().GetActiveScene()->GetChild("MenuTransition"))->Transition([]() {
			Game::GetInstance().GetActiveScene()->GetChild("UI")->SetActive(true)->SetVisible(true);
		});
	});

	CameraGameObject *camera = new CameraGameObject("MainCamera", this);
	// this->AddGameCamera(camera);
	// this->SetActiveCamera(camera);

	Saver *saver = new Saver("Saver", this);
	ReplayManager *replayManager = new ReplayManager("ReplayManager", this);

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
		std::cout << Saver::mEntitySaveData.size() << std::endl;
		((DungeonRoom *)dungeon->GetChild("DungeonRoom"))->EntitysFromSaveData(Saver::mEntitySaveData);
	} else {
		srand(time(0));
		dungeon->Generate(10, rand());
	}

	RoomTransition *roomTransition = new RoomTransition("Transition", this);

	// Pause Menu ==============================================================
	MenuTransition *menuTransition = new MenuTransition("MenuTransition", this);
	GameObject *ui = new GameObject("UI", this);
	ui->SetZIndex(0);
	ui->SetVisible(false);
	ui->SetActive(false);

	ui->AddChild(new TextGameObject("Text", "PAUSE MENU", TextGameObject::TextProperties("default", 300.0f, true), {0.0f, -30.0f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(0);

	Button *continueButton = new Button("ContinueButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, [ui]() {
            if (!ui->GetActive()) return;
            if (Game::GetInstance().GetState() != GameState::GAME_PAUSED) return;
            if (Player::mLevelCleared) {
                Dungeon *dungeon = (Dungeon *)Game::GetInstance().GetActiveScene()->GetChild("Dungeon");
                srand(time(0));
                dungeon->Generate(10, rand());
                Player::mLevelCleared = false;
                Game::GetInstance().GetActiveScene()->GetChild("Player")->SetPosition({0.0f, 0.0f, 0.0f});
                ((ReplayManager*)Game::GetInstance().GetActiveScene()->GetChild("ReplayManager"))->Init();
            }
            Game::GetInstance().GetActiveScene()->GetChild("MenuTransition")->SetVisible(false);
            Game::GetInstance().GetActiveScene()->GetChild("UI")->SetActive(false)->SetVisible(false);
            Game::GetInstance().SetState(GameState::GAME_ACTIVE); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	continueButton->SetPosition({0.0f, -5.0f, 0.0f});
	continueButton->AddChild(new TextGameObject("Text", "CONTINUE", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);

	Button *menuButton = new Button("MenuButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, [ui]() {
            if (!ui->GetActive()) return;
            Game::GetInstance().RequestLoadScene("Menu"); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	menuButton->SetPosition({0.0f, 10.0f, 0.0f});
	menuButton->AddChild(new TextGameObject("Text", "MENU", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);

	Button *exitButton = new Button("ExitButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, [ui]() { 
            if (!ui->GetActive()) return;
            Game::GetInstance().Quit(); }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	exitButton->SetPosition({0.0f, 25.0f, 0.0f});

	Button *replayButton = new Button("ReplayButton", ui, {0.0f, 0.0f, 0.0f}, {192.0f / 2.5, 32.0f / 2.5}, [ui]() { 
            if (!ui->GetActive()) return;
            if (!Player::mLevelCleared) return;
            Dungeon *dungeon = (Dungeon *)Game::GetInstance().GetActiveScene()->GetChild("Dungeon");
            dungeon->Generate(10, dungeon->GetSaveData().seed);
            Game::GetInstance().GetActiveScene()->GetChild("MenuTransition")->SetVisible(false);
            Game::GetInstance().GetActiveScene()->GetChild("UI")->SetActive(false)->SetVisible(false);
            Game::GetInstance().SetState(GameState::GAME_REPLAY); 
            ReplayManager::mOldState = Game::GetInstance().GetState();
            }, new SpriteGameObject("Image", this, "banner", {0.0f, 0.0f, 0.0f}, {192.0f / 2.0, 32.0f / 2.0}));
	replayButton->SetPosition({0.0f, 40.0f, 0.0f});
	replayButton->AddChild(new TextGameObject("Text", "REPLAY", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);
	exitButton->AddChild(new TextGameObject("Text", "EXIT", TextGameObject::TextProperties("default", 190.0f, true), {0.0f, 0.6f, 0.0f}, {20.0f, 20.0f}))->SetZIndex(100);
}

void GameScene::Update(float deltaTime) {
	if (mActive == false) {
		return;
	}

	SceneGameObject::Update(deltaTime);
}

void GameScene::Render() {
	TextGameObject *title = (TextGameObject *)GetChild("UI")->GetChild("Text");
	if (Player::mLevelCleared) {
		title->SetText("LEVEL CLEARED");
	} else {
		title->SetText("PAUSE MENU");
	}

    GetChild("UI")->GetChild("ContinueButton")->SetActive(Player::mLevelCleared)->SetVisible(Player::mLevelCleared);
    bool showReplayButton = Player::mLevelCleared && Game::GetInstance().GetState() != GameState::GAME_OVER && !((ReplayManager *)GetChild("ReplayManager"))->mReplayStarted;
    GetChild("UI")->GetChild("ReplayButton")->SetActive(showReplayButton)->SetVisible(showReplayButton);

	SceneGameObject::Render();
}
