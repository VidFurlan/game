#pragma once

#include "game_window.hpp"
#include "singleton.hpp"
#include "sprite_renderer.hpp"
#include "resource_manager.hpp"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
};

class Game : public Singleton {
   public:
	static Game &GetInstance() {
		static Game instance;
		return instance;
	}

	void Init();
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();

    bool ShouldClose() const;

	GameWindow *GetWindow() const;

	GameState State;
	bool Keys[1024];

   private:
	Game() {}
	GameWindow *mWindow;

	ResourceManager *resourceManager;
    SpriteRenderer *mSpriteRenderer;
};
