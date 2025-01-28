#pragma once

#include "shader.hpp"
#include "texture.hpp"

class PostProcessor {
   public:
	Shader mPostProcessingShader;
	Texture mTexture;
	unsigned int mWidth, mHeight;

	PostProcessor(Shader shader, unsigned int width, unsigned int height);
	void BeginRender();
	void EndRender();
	void Render(float time);
	void Resize(int newWidth, int newHeight);

   private:
	unsigned int MSFBO, FBO;
	unsigned int RBO;
	unsigned int VAO;

	void InitRenderData();
};
