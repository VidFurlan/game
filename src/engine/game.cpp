#include "game.hpp"

void Game::Init() {
	window = new GameWindow(800, 600, "Game");
}

void Game::Run() {
    Image image("image.bmp");
    while (window->IsRunning()) {
        window->SetColor(Color(0.1f, 0.1f, 0.1f));
        window->Draw(image, 200, 200);
        window->Update();
    }
}

void Game::Stop() {
	window->Close();
}

GameWindow *Game::GetWindow() const {
    return window;
}
