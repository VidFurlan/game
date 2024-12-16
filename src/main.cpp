#include <game.hpp>
#include <game_window.hpp>
#include "GLFW/glfw3.h"

int main() {
    Game &game = Game::GetInstance();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

    game.Init();

    while (!game.ShouldClose()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        game.ProcessInput(deltaTime);

        game.Update(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        glfwSwapBuffers(game.GetWindow()->GetWindow());
    }

    game.GetWindow()->Close();

    return 0;
}
