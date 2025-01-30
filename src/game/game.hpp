#pragma once

#include <functional>
#include <map>

#include "game_window.hpp"
#include "post_processor.hpp"
#include "resource_manager.hpp"
#include "scene_game_object.hpp"
#include "singleton.hpp"
#include "sprite_renderer.hpp"

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
	void Run();
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();

	bool ShouldClose() const;

	void AddScene(const std::string &sceneName, std::function<SceneGameObject *()> factory);
	void LoadScene(const std::string &sceneName);

    void SetPostProcessingDisabled(bool disabled);
    bool IsPostProcessingDisabled() const;
    void SetDebugMode(bool debugMode);
    bool IsDebugMode() const;

	GameWindow *GetWindow() const;
	SpriteRenderer *GetSpriteRenderer() const;
	ResourceManager *GetResourceManager() const;
	SceneGameObject *GetActiveScene() const;
    PostProcessor *GetPostProcessor() const;

	GameState State;
	bool Keys[1024];

   private:
	Game() {}
	GameWindow *mWindow = nullptr;

	ResourceManager *resourceManager = nullptr;
	SpriteRenderer *mSpriteRenderer = nullptr;
    PostProcessor *mPostProcessor = nullptr;

    bool mPostProcessingDisabled = false;
    bool mDebugMode = false;

	std::map<std::string, std::function<SceneGameObject *()>> mSceneFactory;
	SceneGameObject *mCurrentScene = nullptr;
};
