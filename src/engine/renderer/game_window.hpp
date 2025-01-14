#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

   private:
	GLFWwindow* window;
};
