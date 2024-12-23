#include "game.hpp"
#include <iostream>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "resource_manager.hpp"
#include "shader.hpp"
#include "sprite_renderer.hpp"

void Game::Init() {
	mWindow = new GameWindow(1200, 800, "Game");

	resourceManager = &ResourceManager::GetInstance();
	resourceManager->LoadShader("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()), 
            static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

	resourceManager->GetShader("sprite").Use().SetInteger("image", 0);
	resourceManager->GetShader("sprite").SetMatrix4("projection", projection);

	mSpriteRenderer = new SpriteRenderer(resourceManager->GetShader("sprite"));
    resourceManager->LoadTexture("assets/character.png", true, "character");
}

void Game::Update(float deltaTime) {
}

void Game::ProcessInput(float deltaTime) {
}

void Game::Render() {
     mSpriteRenderer->DrawSprite(resourceManager->GetTexture("character"), 
             glm::vec2(200.0f, 200.0f), 
             glm::vec2(300.0f, 300.0f), 
             0.0f, 
             glm::vec3(1.0f, 1.0f, 1.0f));
}

GameWindow *Game::GetWindow() const {
	return mWindow;
}

bool Game::ShouldClose() const {
	return glfwWindowShouldClose(mWindow->GetWindow());
}
