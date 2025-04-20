#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "stb_image_write.h"
#include "stb_truetype.h"

// https://github.com/shreyaspranav/stb-truetype-example/blob/main/Main.cpp

class FontRenderer {
   public:
	FontRenderer(std::string path);

	void DrawText(const std::string &text, glm::vec2 position, float scale, glm::vec4 color);

   private:
	const int ATLAS_WIDTH = 1024*2;
	const int ATLAS_HEIGHT = 1024*2;

	const int firstChar = 32;
	const int charCount = 95;
	const float fontSize = 128.0f;

    std::string mFontName;

	stbtt_packedchar *packedChars;
	stbtt_aligned_quad *alignedQuads;

	uint32_t mFontAtlasTexture;
};
