#include "image.hpp"

#include <fstream>
#include <iostream>

Color::Color()
	: r(0), g(0), b(0) {}

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b) {}

Color::~Color() {}

Image::Image() {}

Image::Image(int width, int height)
	: width(width),
	  height(height),
	  colors(std::vector<Color>(width * height)) {}

Image::~Image() {}

Color Image::GetColor(int x, int y) const {
	return colors[y * width + x];
}

void Image::SetColor(int x, int y, const Color &color) {
	colors[y * width + x] = color;
}

void Image::Read(const char *path) {
	std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open file " << path << std::endl;
        return;
    }
    
    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    file.read(reinterpret_cast<char *>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        std::cerr << "The file " << path << " is not a BMP image" << std::endl;
        file.close();
        return;
    }

    unsigned char infoHeader[infoHeaderSize];
    file.read(reinterpret_cast<char *>(infoHeader), infoHeaderSize);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    width = infoHeader[4] + (infoHeader[5] << 8) + (infoHeader[6] << 16) + (infoHeader[7] << 24);
    height = infoHeader[8] + (infoHeader[9] << 8) + (infoHeader[10] << 16) + (infoHeader[11] << 24);

    colors.resize(width * height);

	const int paddingSize = (4 - (width * 3) % 4) % 4;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char color[3];
            file.read(reinterpret_cast<char *>(color), 3);

            SetColor(x, y, Color(color[2] / 255.0f, color[1] / 255.0f, color[0] / 255.0f));
        }

        file.ignore(paddingSize);
    }

    file.close();

    std::cout << "Image read from " << path << std::endl;
}

void Image::Export(const char *path) const {
	std::ofstream file;
	file.open(path, std::ios::out | std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Failed to open file " << path << std::endl;
		return;
	}

	unsigned char bmpPad[3] = {0, 0, 0};
	const int paddingSize = (4 - (width * 3) % 4) % 4;

	const int fileHeaderSize = 14;
	const int infoHeaderSize = 40;
	const int fileSize = fileHeaderSize + infoHeaderSize + 3 * width * height + paddingSize * height;

	// File header
	unsigned char fileHeader[fileHeaderSize];
	memset(fileHeader, 0, fileHeaderSize);

	// Specify BMP
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';
	// File size
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;
	// Pixel data offset
	fileHeader[10] = fileHeaderSize + infoHeaderSize;

	// Info header
	unsigned char infoHeader[infoHeaderSize];
	memset(infoHeader, 0, infoHeaderSize);

	// Info header size
	infoHeader[0] = infoHeaderSize;
	// Width and height
	infoHeader[4] = width;
	infoHeader[5] = width >> 8;
	infoHeader[6] = width >> 16;
	infoHeader[7] = width >> 24;
	infoHeader[8] = height;
	infoHeader[9] = height >> 8;
	infoHeader[10] = height >> 16;
	infoHeader[11] = height >> 24;
	// Planes
	infoHeader[12] = 1;
	// Bits per pixel
	infoHeader[14] = 24;

	file.write(reinterpret_cast<char *>(fileHeader), fileHeaderSize);
	file.write(reinterpret_cast<char *>(infoHeader), infoHeaderSize);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
			unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
			unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

			unsigned char pixel[3] = {b, g, r};

			file.write(reinterpret_cast<char *>(pixel), 3);
		}

		file.write(reinterpret_cast<char *>(bmpPad), paddingSize);
	}

	file.close();

	std::cout << "Image exported to " << path << std::endl;
}
