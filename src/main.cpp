#include "game.hpp"
#include "game_scene.hpp"
#include "game_window.hpp"

#include "demo_scene.hpp"

int main() {
	// Init game
	Game &game = Game::GetInstance();
	game.Init();

	// Load scenes
	game.AddScene("Demo", [&]() { return new DemoScene(); });
	game.AddScene("Game", [&]() { return new GameScene(); });

	game.LoadScene("Game");

	// Run game
	game.Run();

	return 0;
}
