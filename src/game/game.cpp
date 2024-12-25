#include "game.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "resource_manager.hpp"
#include "shader.hpp"
#include "sprite_game_object.hpp"
#include "sprite_renderer.hpp"

SpriteGameObject *spriteGameObject;
void Game::Init() {
	mWindow = new GameWindow(1200, 800, "Game");

	resourceManager = &ResourceManager::GetInstance();
	resourceManager->LoadShader("shaders/sprite_vertex.glsl", "shaders/sprite_fragment.glsl", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow->GetWidth()),
									  static_cast<float>(mWindow->GetHeight()), 0.0f, -1.0f, 1.0f);

	resourceManager->GetShader("sprite").Use().SetInteger("image", 0);
	resourceManager->GetShader("sprite").SetMatrix4("projection", projection);

	mSpriteRenderer = new SpriteRenderer(resourceManager->GetShader("sprite"));
	resourceManager->LoadTexture("assets/walk.png", true, "character");

    spriteGameObject = new SpriteGameObject("character", "character", glm::vec2(0.0f, 0.0f));
}

void Game::Run() {
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(mWindow->GetWindow(), true);  // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	GLuint textureID = resourceManager->GetTexture("character").ID;
	ImVec2 buttonSize(64.0f, 64.0f);

	while (!ShouldClose()) {
		// Game updates
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		ProcessInput(deltaTime);

		Update(deltaTime);

		// Actual rendering
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");	// Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");			// Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);	// Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);			  // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float *)&clear_color);  // Edit 3 floats representing a color

			if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		if (show_another_window) {
			ImGui::Begin("Another Window", &show_another_window);  // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(mWindow->GetWindow());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

int spriteIndex = 0;
float timeSinceLastChange = 0.0f;
void Game::Update(float deltaTime) {
	timeSinceLastChange += deltaTime;
	if (timeSinceLastChange > 0.1f) {
		spriteIndex++;
		spriteIndex %= 3 * 8;
		timeSinceLastChange = 0.0f;
	}
}

void Game::ProcessInput(float deltaTime) {
}

void Game::Render() {
    spriteGameObject->Render();
}

GameWindow *Game::GetWindow() const {
	return mWindow;
}

SpriteRenderer *Game::GetSpriteRenderer() const {
	return mSpriteRenderer;
}

bool Game::ShouldClose() const {
	return glfwWindowShouldClose(mWindow->GetWindow());
}
