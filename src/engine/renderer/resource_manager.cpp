#include "resource_manager.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "game_window.hpp"
#include "image.hpp"

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name) {
	Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(const std::string& name) {
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char* file, bool alpha, const std::string& name) {
	Textures[name] = LoadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(const std::string& name) {
	return Textures[name];
}

void ResourceManager::Clear() {
	for (auto it : Shaders) {
		glDeleteProgram(it.second.ID);
	}

	for (auto it : Textures) {
		glDeleteTextures(1, &it.second.ID);
	}
}

Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try {
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	} catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::LoadTextureFromFile(const char* file, bool alpha) {
	Texture texture;
	if (alpha) {
		texture.InternalFormat = GL_RGBA;
		texture.ImageFormat = GL_RGBA;
	}
	int width, height, nrChannels;
	unsigned char* data = Image(file).GetData();
	texture.Generate(width, height, data);
	return texture;
}
