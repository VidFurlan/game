#include <minifb.h>
#include <iostream>
#include "image/image.hpp"

int main() {
	const int width = 800;
	const int height = 600;
	Image image(width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.SetColor(x, y,
						   Color((float)x / (float)width,
								 1.0f - (float)x / (float)width,
								 (float)y / (float)height));
		}
	}
	image.Export("image.bmp");

    struct mfb_window *window = mfb_open_ex("my display", 800, 600, WF_RESIZABLE);
    if (!window) return 0;

    auto buffer = (uint32_t *) malloc(800 * 600 * 4);

    do {
        int state;

        for (int y = 0; y < 600; y++) {
            for (int x = 0; x < 800; x++) {
                Color color = image.GetColor(x, y);
                buffer[y * 800 + x] = (uint32_t)(color.r * 255) << 16 |
                                      (uint32_t)(color.g * 255) << 8 |
                                      (uint32_t)(color.b * 255);
            }
        }

        state = mfb_update_ex(window, buffer, 800, 600);

        if (state < 0) {
            window = NULL;
            break;
        }
    } while(mfb_wait_sync(window));

    return 0;
}
