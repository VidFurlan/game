#include "../engine/game.hpp"

#include <iostream>

#include "debug/debug_renderer.hpp"
#include "debug/imgui_helper.hpp"
#include "game_objects/colliders/collision_manager.hpp"
#include "game_objects/scene_game_object.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "renderer/resource_manager.hpp"
#include "renderer/shader.hpp"
#include "renderer/sprite_renderer.hpp"
#include "shapes/polygon2d.hpp"

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
		// Game updates
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		ProcessInput(deltaTime);

		Update(deltaTime);

		CollisionManager::GetInstance().Update(deltaTime);

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
