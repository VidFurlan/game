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
    Image(const char *path);
	Image(int width, int height);
    ~Image();

    unsigned char *GetData() const;

    int GetWidth() const;
    int GetHeight() const;
    Color GetColor(int x, int y) const;
    void SetColor(int x, int y, const Color &color);
    
    void Read(const char *path);
    void Export(const char *path) const;

   private:
    int mWidth, mHeight;
    unsigned char *data;
};
