#pragma once

#include <stdint.h>

#include "image/image.hpp"

class GameWindow {
   public:
	GameWindow(int width, int height, const char *title);
	~GameWindow();

	bool IsRunning() const;
	void Update();
	void Close();

	void Draw(const Image &image);
	void Draw(const Image &image, int x, int y);
    void SetColor(const Color &color);

   private:
    static void resize(struct mfb_window *window, int width, int height);

	struct mfb_window *window;
	uint32_t *buffer;
	int mWidth, mHeight;
};
