#include "game.hpp"

void Game::Init() {
	mWindow = new GameWindow(800, 800, "Game");
}

void Game::Update(float deltaTime) {
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
