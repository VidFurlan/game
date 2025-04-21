#include "game_window.hpp"

#include <GL/glew.h>
#include <GL/glu.h>

#include <iostream>

#include "GLFW/glfw3.h"
#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "resource_manager.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GameWindow::GameWindow(int width, int height, const char* title) {
	if (!glfwInit()) {
		std::cout << "GLFW Initialization Failed" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_STENCIL_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

GameWindow::~GameWindow() {
	ResourceManager::GetInstance().Clear();
	glfwTerminate();
}

void GameWindow::Close() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* GameWindow::GetWindow() const {
	return window;
}

int GameWindow::GetWidth() const {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

int GameWindow::GetHeight() const {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}

glm::mat4 GameWindow::GetMVP() const {
    return mMvp;
}

void GameWindow::Resize(int width, int height) {
	/* Resizing of viewport using black bars
	float desiredAspectRatio = Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetWidth() /
	                           static_cast<float>(Game::GetInstance().GetActiveScene()->GetActiveCamera()->GetHeight());

	int viewportWidth, viewportHeight;
	int viewportX = 0, viewportY = 0;

	float windowAspectRatio = width / static_cast<float>(height);
	if (windowAspectRatio > desiredAspectRatio) {
	    viewportHeight = height;
	    viewportWidth = static_cast<int>(height * desiredAspectRatio);
	    viewportX = (width - viewportWidth) / 2;
	} else {
	    viewportWidth = width;
	    viewportHeight = static_cast<int>(width / desiredAspectRatio);
	    viewportY = (height - viewportHeight) / 2;
	}

	glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
	glScissor(viewportX, viewportY, viewportWidth, viewportHeight);

	Game::GetInstance().GetPostProcessor()->Resize(viewportWidth, viewportHeight);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(viewportWidth),
	                                  static_cast<float>(viewportHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetInstance().GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetInstance().GetShader("sprite").SetMatrix4("projection", projection);
	*/
	glViewport(0, 0, width, height);
	mMvp = glm::ortho(0.0f, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()), 0.0f, -1.0f, 1.0f);
	Game::GetInstance().GetPostProcessor()->Resize(width, height);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetInstance().GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetInstance().GetShader("sprite").SetMatrix4("projection", projection);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			if (Game::GetInstance().Keys[key] == false && Game::GetInstance().mOnPressKeyCallbacks[key].size()) {
				for (auto& [id, callback] : Game::GetInstance().mOnPressKeyCallbacks[key]) {
					callback();
				}
			}
			Game::GetInstance().Keys[key] = true;
		} else if (action == GLFW_RELEASE) {
			if (Game::GetInstance().Keys[key] == true && Game::GetInstance().mOnReleaseKeyCallbacks[key].size()) {
				for (auto& [id, callback] : Game::GetInstance().mOnReleaseKeyCallbacks[key]) {
					callback();
				}
			}
			Game::GetInstance().Keys[key] = false;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	Game::GetInstance().MousePosition = {xpos, ypos};
}

void framebuffer_size_callback(GLFWwindow* window,
                               int widthOfFramebuffer,
                               int heightOfFramebuffer) {
	Game::GetInstance().GetWindow()->Resize(widthOfFramebuffer, heightOfFramebuffer);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	key_callback(window, button, 0, action, mods);
}
