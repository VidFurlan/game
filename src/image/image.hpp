#pragma once

#include <vector>
struct Color {
	float r, g, b;
	Color();
	Color(float r, float g, float b);
	~Color();
};

class Image {
   public:
    Image();
	Image(int width, int height);
    ~Image();

    Color GetColor(int x, int y) const;
    void SetColor(int x, int y, const Color &color);
    
    void Read(const char *path);
    void Export(const char *path) const;

   private:
    int width, height;
    std::vector<Color> colors;
};
