#include "game.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "resource_manager.hpp"
#include "shader.hpp"
#include "sprite_renderer.hpp"
#include "texture.hpp"

void Game::Init() {
	mWindow = new GameWindow(800, 800, "Game");

	resourceManager = &ResourceManager::GetInstance();
	resourceManager->LoadShader("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()), static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

	resourceManager->GetShader("sprite").Use();
	resourceManager->GetShader("sprite").SetMatrix4("projection", projection);

	Shader shader = resourceManager->GetShader("sprite");
	mSpriteRenderer = new SpriteRenderer(shader);
	resourceManager->LoadTexture("assets/image.bmp", true, "image");
}

void Game::Update(float deltaTime) {
	Texture texture = resourceManager->GetTexture("image");
	mSpriteRenderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::ProcessInput(float deltaTime) {
}

void Game::Render() {
}

GameWindow *Game::GetWindow() const {
	return mWindow;
}

bool Game::ShouldClose() const {
	return glfwWindowShouldClose(mWindow->GetWindow());
}
