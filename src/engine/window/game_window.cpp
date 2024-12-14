#include "game_window.hpp"

#include <MiniFB.h>

#include <iostream>

#include "MiniFB_enums.h"
#include "game.hpp"

void GameWindow::resize(struct mfb_window *window, int width, int height) {
	GameWindow *gameWindow = Game::GetInstance().GetWindow();
	mfb_set_viewport_best_fit(window, gameWindow->mWidth, gameWindow->mHeight);
	gameWindow->mWidth = width;
	gameWindow->mHeight = height;
    free(gameWindow->buffer);
    gameWindow->buffer = (uint32_t *)malloc(width * height * 4);
}

GameWindow::GameWindow(int width, int height, const char *title)
	: window(nullptr), buffer(nullptr), mWidth(width), mHeight(height) {
	window = mfb_open_ex(title, width, height, WF_RESIZABLE);
	if (!window) return;

	mfb_set_resize_callback(window, resize);

	buffer = (uint32_t *)malloc(width * height * sizeof(uint32_t));
	if (!buffer) {
		std::cerr << "Failed to allocate buffer" << std::endl;
		mfb_close(window);
		window = nullptr;
	}
}

GameWindow::~GameWindow() {
	free(buffer);
	mfb_close(window);
}

bool GameWindow::IsRunning() const {
	if (window == NULL) return false;
	return mfb_wait_sync(window);
}

void GameWindow::Update() {
	int state;

	state = mfb_update_ex(window, buffer, mWidth, mHeight);

	if (state < 0) {
		window = nullptr;
        return;
	}

    mWidth = mfb_get_window_width(window);
    mHeight = mfb_get_window_height(window);
}

void GameWindow::Draw(const Image &image) {
	if (!window) return;

	Draw(image, 0, 0);
}

void GameWindow::Draw(const Image &image, int x, int y) {
	if (!window) return;

	for (int j = 0; j < image.GetHeight(); j++) {
		for (int i = 0; i < image.GetWidth(); i++) {
			if (i + x < 0 || i + x >= mWidth || j + y < 0 || j + y >= mHeight) {
				continue;
			}

			buffer[(j + y) * mWidth + (i + x)] = (uint32_t)(image.GetColor(i, j).r * 255) << 16 |
												 (uint32_t)(image.GetColor(i, j).g * 255) << 8 |
												 (uint32_t)(image.GetColor(i, j).b * 255);
		}
	}
}

void GameWindow::SetColor(const Color &color) {
	for (int j = 0; j < mHeight; j++) {
		for (int i = 0; i < mWidth; i++) {
			buffer[j * mWidth + i] = (uint32_t)(color.r * 255) << 16 |
									 (uint32_t)(color.g * 255) << 8 |
									 (uint32_t)(color.b * 255);
		}
	}
}

void GameWindow::Close() {
	if (!window) return;
	mfb_close(window);
	window = nullptr;
}
