#include "font_renderer.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "batch_renderer.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtc/type_ptr.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

FontRenderer::FontRenderer(std::string path) {
	std::ifstream inputFile(path, std::ios::binary);
	inputFile.seekg(0, std::ios::end);
	std::streampos end = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);
	std::streampos begin = inputFile.tellg();
	size_t fileSize = static_cast<size_t>(end - begin);

	uint8_t *fontData = new uint8_t[fileSize];
	inputFile.read((char *)fontData, fileSize);

	int fontCount = stbtt_GetNumberOfFonts(fontData);
	if (fontCount == -1)
		std::cerr << "Invalid font data." << std::endl;
	else
		std::cout << "File contains " << fontCount << " fonts." << std::endl;

	uint8_t *fontAtlasBitmap = new uint8_t[ATLAS_WIDTH * ATLAS_HEIGHT];

	packedChars = new stbtt_packedchar[charCount];
	alignedQuads = new stbtt_aligned_quad[charCount];
	stbtt_pack_context ctx;

	stbtt_PackBegin(
	    &ctx,                              // stbtt_pack_context (this call will initialize it)
	    (unsigned char *)fontAtlasBitmap,  // Font Atlas bitmap data
	    ATLAS_WIDTH,                       // Width of the font atlas texture
	    ATLAS_HEIGHT,                      // Height of the font atlas texture
	    0,                                 // Stride in bytes
	    1,                                 // Padding between the glyphs
	    nullptr);

	stbtt_PackFontRange(
	    &ctx,        // stbtt_pack_context
	    fontData,    // Font Atlas texture data
	    0,           // Font Index
	    fontSize,    // Size of font in pixels. (Use STBTT_POINT_SIZE(fontSize) to use points)
	    firstChar,   // Code point of the first character
	    charCount,   // No. of charecters to be included in the font atlas
	    packedChars  // stbtt_packedchar array, this struct will contain the data to render a glyph
	);
	stbtt_PackEnd(&ctx);

	for (int i = 0; i < charCount; i++) {
		float unusedX, unusedY;

		stbtt_GetPackedQuad(
		    packedChars,   // Array of stbtt_packedchar
		    ATLAS_WIDTH,   // Width of the font atlas texture
		    ATLAS_HEIGHT,  // Height of the font atlas texture
		    i,             // Index of the glyph
		    &unusedX,
		    &unusedY,          // current position of the glyph in screen pixel coordinates, (not required as we have a different corrdinate system)
		    &alignedQuads[i],  // stbtt_alligned_quad struct. (this struct mainly consists of the texture coordinates)
		    0                  // Allign X and Y position to a integer (doesn't matter because we are not using 'unusedX' and 'unusedY')
		);
	}

	// stbi_write_png("fontAtlas.png", ATLAS_WIDTH, ATLAS_HEIGHT, 1, fontAtlasBitmap, ATLAS_WIDTH);

	glGenTextures(1, &mFontAtlasTexture);
	glBindTexture(GL_TEXTURE_2D, mFontAtlasTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, ATLAS_WIDTH, ATLAS_HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, fontAtlasBitmap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] fontAtlasBitmap;
	delete[] fontData;
}

void FontRenderer::DrawText(const std::string &text, glm::vec2 position, float scale, glm::vec4 color) {
	int order[6] = {0, 1, 2, 0, 2, 3};
	float pixelScale = 2.0f / Game::GetInstance().GetWindow()->GetHeight();

	glm::vec3 localPosition = glm::make_vec3(position);
	for (char ch : text) {
		if (ch >= firstChar && ch <= firstChar + charCount) {
			stbtt_packedchar *packedChar = &packedChars[ch - firstChar];
			stbtt_aligned_quad *alignedQuad = &alignedQuads[ch - firstChar];

			glm::vec2 glyphSize = {
			    (packedChar->x1 - packedChar->x0) * pixelScale * scale,
			    (packedChar->y1 - packedChar->y0) * pixelScale * scale};

			glm::vec2 glyphBottomLeft = {
			    localPosition.x + (packedChar->xoff * pixelScale * scale),
			    localPosition.y - (packedChar->yoff + packedChar->y1 - packedChar->y0) * pixelScale * scale};

			glm::vec2 vertices[4] = {
			    {glyphBottomLeft.x + glyphSize.x, glyphBottomLeft.y + glyphSize.y},
			    {glyphBottomLeft.x, glyphBottomLeft.y + glyphSize.y},
			    {glyphBottomLeft.x, glyphBottomLeft.y},
			    {glyphBottomLeft.x + glyphSize.x, glyphBottomLeft.y}};

			glm::vec2 uvs[4] = {
			    {alignedQuad->s0, alignedQuad->t1},
			    {alignedQuad->s1, alignedQuad->t1},
			    {alignedQuad->s1, alignedQuad->t0},
			    {alignedQuad->s0, alignedQuad->t0}};

			Game::GetInstance().GetBatchRenderer()->pushObject(mFontAtlasTexture, localPosition, 
                    {alignedQuad->s0, alignedQuad->t0, alignedQuad->s1, alignedQuad->t1}, glm::vec2(glyphSize.x, glyphSize.y) / GameObject::GAME_SCALE_FACTOR, color, "default_font");

			localPosition.x += packedChar->xadvance * pixelScale * scale;
		} else if (ch == '\n') {
			localPosition.y -= fontSize * pixelScale * scale;
			localPosition.x = position.x;
		}
	}
}
