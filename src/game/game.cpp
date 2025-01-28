#include "game.hpp"

#include <iostream>

#include "debug_renderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "imgui_helper.hpp"
#include "polygon2d.hpp"
#include "resource_manager.hpp"
#include "scene_game_object.hpp"
#include "shader.hpp"
#include "sprite_renderer.hpp"

void Game::Init() {
	if (mWindow != nullptr) delete mWindow;
	mWindow = new GameWindow(1200, 800, "Game");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()),
									  static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

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

		// Color for black bars
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		// Background color
		glm::vec3 bgColor = GetActiveScene()->GetBackgroundColor();
		glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glm::vec3 bgColor = GetActiveScene()->GetBackgroundColor();
		//glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
		//glEnable(GL_SCISSOR_TEST);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glDisable(GL_SCISSOR_TEST);

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

void Game::SetPostProcessingDisabled(bool disabled) {
	mPostProcessingDisabled = disabled;
}

bool Game::IsPostProcessingDisabled() const {
	return mPostProcessingDisabled;
}

SceneGameObject *Game::GetActiveScene() const {
	return mCurrentScene;
}

PostProcessor *Game::GetPostProcessor() const {
	return mPostProcessor;
}
