#include <game.hpp>

int main() {
    Game::GetInstance().Init();

    Game::GetInstance().Run();

    Game::GetInstance().Stop();

    return 0;
}
