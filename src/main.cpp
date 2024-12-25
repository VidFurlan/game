#include <game.hpp>
#include <game_window.hpp>

int main() {
	Game &game = Game::GetInstance();

	game.Init();

	game.Run();

	game.GetWindow()->Close();

	return 0;
}
