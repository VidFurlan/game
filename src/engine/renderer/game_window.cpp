#include "game_window.hpp"

#include <GL/glew.h>

#include <iostream>

#include "GLFW/glfw3.h"
#include "game.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "resource_manager.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GameWindow::GameWindow(int width, int height, const char* title) {
	if (!glfwInit()) {
		std::cout << "GLFW Initialization Failed" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			Game::GetInstance().Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Game::GetInstance().Keys[key] = false;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
