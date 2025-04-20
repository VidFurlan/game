#include "../engine/game.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

#include "collision_manager.hpp"
#include "debug/imgui_helper.hpp"
#include "game_objects/scene_game_object.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/fwd.hpp"
#include "renderer/resource_manager.hpp"
#include "renderer/shader.hpp"
#include "renderer/sprite_renderer.hpp"

void Game::Init() {
	if (mWindow != nullptr) delete mWindow;
	mWindow = new GameWindow(1200, 800, "Game");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()), static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

	// Load generic sprite shader
	resourceManager = &ResourceManager::GetInstance();

	resourceManager->LoadShader("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl", nullptr, "sprite");
	resourceManager->GetShader("sprite").Use().SetInteger("image", 0);
	resourceManager->GetShader("sprite").SetMatrix4("projection", projection);

	resourceManager->LoadShader("shaders/post_processing_vertex.glsl", "shaders/post_processing_fragment.glsl", nullptr, "post_processing");

	if (mPostProcessor != nullptr) delete mPostProcessor;
	mPostProcessor = new PostProcessor(resourceManager->GetShader("post_processing"), mWindow->GetWidth(), mWindow->GetHeight());

	if (mCurrentScene != nullptr) delete mCurrentScene;
	mSpriteRenderer = new SpriteRenderer(resourceManager->GetShader("sprite"));

	if (mBatchRenderer != nullptr) delete mBatchRenderer;
	mBatchRenderer = new BatchRenderer(2000000);
}

void Game::Run() {
	ImGuiHelper::Init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!ShouldClose()) {
		LoadScene();

		// Game updates
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		ProcessInput(deltaTime);

		Update(deltaTime);
		ApplyDeleteRequests();

		CollisionManager::GetInstance().Update(deltaTime);

		LateUpdate(deltaTime);
		ApplyDeleteRequests();

		if (mWindow->GetWidth() == 0 || mWindow->GetHeight() == 0) {
			continue;
		}

		// Render ImGui
		ImGuiHelper::NewFrame();
		ImGuiHelper::ImGuiDebugMenu();

		// Rendering
		if (!mPostProcessingDisabled) {
			mPostProcessor->BeginRender();
		}

		// Background color
		glm::vec3 bgColor = GetActiveScene()->GetBackgroundColor();
		glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Render();

		if (!mPostProcessingDisabled) {
			mPostProcessor->EndRender();
			mPostProcessor->Render(glfwGetTime());
		}

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

void Game::LateUpdate(float deltaTime) {
	if (mCurrentScene != nullptr) {
		mCurrentScene->LateUpdate(deltaTime);
	}
}

void Game::ProcessInput(float deltaTime) {
}

void Game::Render() {
	glm::mat4 ort = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()), static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mBatchRenderer->mMvp[i][j] = ort[i][j];
		}
	}

	if (mCurrentScene != nullptr) {
		mCurrentScene->Render();
	}

	mBatchRenderer->flush();
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
	return glfwWindowShouldClose(mWindow->GetWindow()) || mShouldClose;
}

void Game::AddScene(const std::string &sceneName, std::function<SceneGameObject *()> factory) {
	mSceneFactory[sceneName] = factory;
}

void Game::RequestLoadScene(const std::string &sceneName, ...) {
	mSceneToLoad = sceneName;
}

void Game::LoadScene() {
	if (mSceneToLoad == "") return;
	if (mCurrentScene) {
		delete mCurrentScene;
	}
	auto it = mSceneFactory.find(mSceneToLoad);
	if (it != mSceneFactory.end()) {
		mCurrentScene = it->second();
		mCurrentScene->Init();
	} else {
		std::cerr << "Scene not found: " << mSceneToLoad << std::endl;
	}
	mSceneToLoad = "";
}

void Game::SetPostProcessingDisabled(bool disabled) {
	mPostProcessingDisabled = disabled;
}

bool Game::IsPostProcessingDisabled() const {
	return mPostProcessingDisabled;
}

void Game::SetDebugMode(bool debugMode) {
	mDebugMode = debugMode;
}

bool Game::IsDebugMode() const {
	return mDebugMode;
}

SceneGameObject *Game::GetActiveScene() const {
	return mCurrentScene;
}

PostProcessor *Game::GetPostProcessor() const {
	return mPostProcessor;
}

BatchRenderer *Game::GetBatchRenderer() const {
	return mBatchRenderer;
}

void Game::SetState(GameState state) {
	State = state;
}

GameState Game::GetState() const {
	return State;
}

void Game::RequestDelete(GameObject *gameObject) {
	mGameObjectsToDelete.push_back(gameObject);
}

void Game::ApplyDeleteRequests() {
	for (auto gameObject : mGameObjectsToDelete) {
		delete gameObject;
	}
	mGameObjectsToDelete.clear();
}

void Game::AddOnPressKeyCallback(int key, std::string id, KeyCallback callback) {
	if (key >= 0 && key < 1024) {
		mOnPressKeyCallbacks[key][id] = callback;
    }
}

void Game::AddOnReleaseKeyCallback(int key, std::string id, KeyCallback callback) {
	if (key >= 0 && key < 1024) {
		mOnReleaseKeyCallbacks[key][id] = callback;
	}
}

void Game::RemoveOnPressKeyCallback(int key, std::string id) {
	if (key >= 0 && key < 1024) {
		mOnPressKeyCallbacks[key].erase(id);
	}
}

void Game::RemoveOnReleaseKeyCallback(int key, std::string id) {
	if (key >= 0 && key < 1024) {
        mOnReleaseKeyCallbacks[key].erase(id);
	}
}

void Game::ClearOnPressKeyCallbacks(int key) {
	if (key >= 0 && key < 1024) {
		mOnPressKeyCallbacks[key].clear();
	}
}

void Game::ClearOnReleaseKeyCallbacks(int key) {
	if (key >= 0 && key < 1024) {
		mOnReleaseKeyCallbacks[key].clear();
	}
}

void Game::AddFont(std::string path, std::string id) {
    if (mFontRenderers.find(id) != mFontRenderers.end()) {
        std::cerr << "Font with id " << id << " already exists." << std::endl;
        return;
    }
    mFontRenderers[id] = new FontRenderer(path);
}

FontRenderer *Game::GetFontRenderer(std::string id) {
    auto it = mFontRenderers.find(id);
    if (it != mFontRenderers.end()) {
        return it->second;
    } else {
        std::cerr << "Font with id " << id << " not found." << std::endl;
        return nullptr;
    }
}

void Game::Quit() {
	glfwTerminate();
	mShouldClose = true;
}
