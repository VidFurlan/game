#pragma once

#include <cstring>

#include "game_window.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "texture.hpp"

class BatchRenderer {
   public:
	struct Object {
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec4 uv = glm::vec4(0.0f);
		glm::vec2 size = glm::vec2(1.0f);
		glm::vec3 color = glm::vec3(1.0f);
	};

	typedef struct {
		float cols[4][4];
	} Matrix;

	struct Vertex {
		glm::vec2 position;
		glm::vec2 uv;
	};

	BatchRenderer(int maxCapacity);
	~BatchRenderer();

	void pushObject(Texture &texture, glm::vec2 position = glm::vec2(0.0f), glm::vec4 uv = {0.0f, 0.0f, 1.0f, 1.0f}, glm::vec2 size = glm::vec2(0.0f), glm::vec3 color = glm::vec3(1.0f));
	void pushVertex(Texture &texture, Vertex vertex);
	void flush();

   private:
	GLuint mShader;
	GLuint mVao;
	GLuint mVbo;
	int mCount;
	int mMaxCount;
	Vertex *mVertices;

	GLuint mTexture;

   public:
	float mMvp[4][4];
};
