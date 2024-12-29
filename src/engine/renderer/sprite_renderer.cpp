#include "sprite_renderer.hpp"

#include <iostream>

#include "game_window.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"

SpriteRenderer::SpriteRenderer(Shader &shader) {
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData() {
	GLuint posVBO, texVBO;
	// Pos VBO
	GLfloat positions[] = {
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f};

	// Texture VBO
	GLfloat texCoords[] = {
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f};

	glGenVertexArrays(1, &this->quadVAO);
	glBindVertexArray(this->quadVAO);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);

	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
								float u1, float v1, float u2, float v2,
								glm::vec2 size, float rotate, glm::vec3 color) {
	this->shader.Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("spriteColor", color);
    this->shader.SetBool("useMask", false);

	// clang-format off
    GLfloat texCoords[] = {
        u1, v2,
        u2, v1,
        u1, v1,

        u1, v2,
        u2, v2,
        u2, v1,

    };
	// clang-format on

	glBindVertexArray(this->quadVAO);

	GLuint texVBO;
	glGenBuffers(1, &texVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &texVBO);
}

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
								glm::vec2 size, float rotate, glm::vec3 color) {
	this->DrawSprite(texture, position, 0.0f, 0.0f, 1.0f, 1.0f, size, rotate, color);
}

void SpriteRenderer::DrawSpriteSheet(Texture &texture, glm::vec2 position, int index, int rows, int cols,
									 glm::vec2 size, float rotate, glm::vec3 color) {
	float u1 = (index % cols) / (float)cols;
	float v1 = (index / cols) / (float)rows;
	float u2 = (index % cols + 1) / (float)cols;
	float v2 = (index / cols + 1) / (float)rows;

	this->DrawSprite(texture, position, u1, v1, u2, v2, size, rotate, color);
}

void SpriteRenderer::DrawSpriteWithMask(Texture &spriteTexture, Texture &maskTexture,
                                        glm::vec2 position, glm::vec2 size, float rotate,
                                        glm::vec3 color) {
    this->shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);
    this->shader.SetBool("useMask", true);

    glActiveTexture(GL_TEXTURE0);
    spriteTexture.Bind();
    this->shader.SetInteger("spriteTexture", 0);

    glActiveTexture(GL_TEXTURE1);
    maskTexture.Bind();
    this->shader.SetInteger("maskTexture", 1);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
