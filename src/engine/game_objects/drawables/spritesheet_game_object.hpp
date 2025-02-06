#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "abstract_image_game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

class SpriteSheetGameObject : public AbstractImageGameObject {
   public:
	SpriteSheetGameObject(std::string name, std::string textureName, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteSheetGameObject(std::string name, GameObject *parent, std::string textureName, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteSheetGameObject(std::string name, Texture &texture, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f), glm::vec3 color = glm::vec3(1.0f));
	SpriteSheetGameObject(std::string name, GameObject *parent, Texture &texture, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale = glm::vec2(1.0f), glm::vec3 color = glm::vec3(1.0f));

	void Render() override;

	SpriteSheetGameObject *SetSpriteSheetFrame(int frame);
	SpriteSheetGameObject *SetSpriteSheetFrame(glm::vec2 frame);

	SpriteSheetGameObject *AddFrameSequence(std::string name, std::vector<glm::vec2> frames);

	std::vector<glm::vec2> *GetFrameSequence(std::string name) const;
	glm::vec2 GetFrameFromSequence(std::string name) const;
	unsigned int GetFrameIndex() const;

   private:
	std::map<std::string, std::vector<glm::vec2>> mFrameSequences;
	std::pair<unsigned int, unsigned int> mFramesResolution;
	unsigned int mFrameIndex = 0;
};
