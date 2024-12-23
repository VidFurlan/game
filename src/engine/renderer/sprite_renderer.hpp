#pragma once

#include <glm/fwd.hpp>

#include "game_window.hpp"
#include "shader.hpp"
#include "texture.hpp"

class SpriteRenderer {
   public:
	SpriteRenderer(Shader &shader);
	~SpriteRenderer();

	void DrawSprite(Texture &texture, glm::vec2 position,
					glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
					glm::vec3 color = glm::vec3(1.0f));

   private:
	Shader shader;
	GLuint quadVAO;

	void initRenderData();
};
