#include "game.hpp"

#include <iostream>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "imgui_helper.hpp"
#include "resource_manager.hpp"
#include "scene_game_object.hpp"
#include "shader.hpp"
#include "sprite_renderer.hpp"

void Game::Init() {
	mWindow = new GameWindow(1200, 800, "Game");

	// Load generic sprite shader
	resourceManager = &ResourceManager::GetInstance();
	resourceManager->LoadShader("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()),
									  static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

	resourceManager->GetShader("sprite").Use().SetInteger("image", 0);
	resourceManager->GetShader("sprite").SetMatrix4("projection", projection);

	mSpriteRenderer = new SpriteRenderer(resourceManager->GetShader("sprite"));
	resourceManager->LoadTexture("assets/walk.png", true, "character");
}

void Game::Run() {
	ImGuiHelper::Init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!ShouldClose()) {
		// Game updates
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		ProcessInput(deltaTime);

		Update(deltaTime);

		// Actual rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGuiHelper::NewFrame();
		ImGuiHelper::ImGuiDebugMenu();

		Render();

		ImGuiHelper::Render();

		glfwSwapBuffers(mWindow->GetWindow());
	}

	ImGuiHelper::Shutdown();
}

void Game::Update(float deltaTime) {
	if (mCurrentScene != nullptr) {
		mCurrentScene->Update(deltaTime);
	}
}

void Game::ProcessInput(float deltaTime) {
}

void Game::Render() {
	if (mCurrentScene != nullptr) {
		mCurrentScene->Render();
	}
}

GameWindow *Game::GetWindow() const {
	return mWindow;
}

SpriteRenderer *Game::GetSpriteRenderer() const {
	return mSpriteRenderer;
}

ResourceManager *Game::GetResourceManager() const {
	return resourceManager;
}

bool Game::ShouldClose() const {
	return glfwWindowShouldClose(mWindow->GetWindow());
}

void Game::AddScene(const std::string &sceneName, std::function<SceneGameObject *()> factory) {
	mSceneFactory[sceneName] = factory;
}

void Game::LoadScene(const std::string &sceneName) {
	if (mCurrentScene) {
		delete mCurrentScene;
	}
	auto it = mSceneFactory.find(sceneName);
	if (it != mSceneFactory.end()) {
		mCurrentScene = it->second();
		mCurrentScene->Init();
	} else {
		std::cerr << "Scene not found: " << sceneName << std::endl;
	}
}

SceneGameObject *Game::GetActiveScene() const {
    return mCurrentScene;
}
