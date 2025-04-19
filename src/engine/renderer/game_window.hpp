#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/ext/matrix_float4x4.hpp"

class GameWindow {
   public:
	GameWindow(int width, int height, const char* title);
	~GameWindow();

	void Close();
	void LoadTexture(const unsigned char* data, int width, int height);

	void Resize(int width, int height);

	GLFWwindow* GetWindow() const;
	int GetWidth() const;
	int GetHeight() const;

    glm::mat4 GetMVP() const;

   private:
	GLFWwindow* window;
    glm::mat4 mMvp;
};
