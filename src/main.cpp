#include "demo_scene.hpp"
#include "game.hpp"
#include "game_scene.hpp"
#include "menu_scene.hpp"
#include "scoreboard_scene.hpp"

int main() {
	// Init game
	Game &game = Game::GetInstance();
	game.Init();

	// Load shaders
	ResourceManager::GetInstance().LoadShader("shaders/font_vertex.glsl", "shaders/font_fragment.glsl", nullptr, "default_font");
	ResourceManager::GetInstance().LoadShader("shaders/batch_renderer_vertex.glsl", "shaders/batch_renderer_fragment.glsl", nullptr, "default_sprite");

	// Load fonts
	game.AddFont("assets/fonts/alagard.ttf", "default");
	game.AddFont("assets/fonts/slkscr.ttf", "slkscr");

	// Manage scenes
	game.AddScene("Demo", [&]() { return new DemoScene(); });
	game.AddScene("Menu", [&]() { return new MenuScene(); });
	game.AddScene("Game", [&]() { return new GameScene(); });
	game.AddScene("Scoreboard", [&]() { return new ScoreboardScene(); });

	game.RequestLoadScene("Menu");

	// Run game
	game.Run();

	return 0;
}
