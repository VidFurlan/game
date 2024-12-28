#include <game.hpp>
#include <game_window.hpp>

#include "main_menu_scene.hpp"

int main() {
	// Init game
	Game &game = Game::GetInstance();
	game.Init();

	// Load scenes
	game.AddScene("MainMenu", [&]() { return new MainMenuScene(); });

	game.LoadScene("MainMenu");

	// Run game
	game.Run();

	return 0;
}
