#pragma once

#include <glm/fwd.hpp>

#include "game_window.hpp"
#include "shader.hpp"
#include "texture.hpp"

class SpriteRenderer {
   public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

	void DrawSprite(Texture &texture, glm::vec2 position, float u1, float v1, float u2, float v2, glm::vec2 size = glm::vec2(10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

	void DrawSpriteSheet(Texture &texture, glm::vec2 position, int index, int rows, int cols, glm::vec2 size = glm::vec2(10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

	void DrawSpriteWithMask(Texture &spriteTexture, Texture &maskTexture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

   private:
	Shader shader;
	GLuint quadVAO;

	void initRenderData();
};
