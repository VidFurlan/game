#pragma once

#include <map>
#include <string>

#include "shader.hpp"
#include "singleton.hpp"
#include "texture.hpp"

class ResourceManager : public Singleton {
   public:
	static ResourceManager& GetInstance() {
		static ResourceManager instance;
		return instance;
	}

	Texture LoadTexture(const char* file, bool alpha, const std::string& name);
	Texture &GetTexture(const std::string& name);
	Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name);
	Shader &GetShader(const std::string& name);
	void Clear();

   private:
	std::map<std::string, Texture> Textures;
	std::map<std::string, Shader> Shaders;

	Texture LoadTextureFromFile(const char* file, bool alpha);
	Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile);
};
