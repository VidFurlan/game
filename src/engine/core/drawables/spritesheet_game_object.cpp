#include "spritesheet_game_object.hpp"

#include <iostream>

#include "abstract_image_game_object.hpp"
#include "game.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

SpriteSheetGameObject::SpriteSheetGameObject(std::string name, std::string textureName, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: AbstractImageGameObject(name, textureName, pos, scale, color), mFramesResolution(framesResolution) {
}

SpriteSheetGameObject::SpriteSheetGameObject(std::string name, GameObject *parent, std::string textureName, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: AbstractImageGameObject(name, parent, textureName, pos, scale, color), mFramesResolution(framesResolution) {
}

SpriteSheetGameObject::SpriteSheetGameObject(std::string name, Texture &texture, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: AbstractImageGameObject(name, texture, pos, scale, color), mFramesResolution(framesResolution) {
}

SpriteSheetGameObject::SpriteSheetGameObject(std::string name, GameObject *parent, Texture &texture, std::pair<unsigned int, unsigned int> framesResolution, glm::vec3 pos, glm::vec2 scale, glm::vec3 color)
	: AbstractImageGameObject(name, parent, texture, pos, scale, color), mFramesResolution(framesResolution) {
}

void SpriteSheetGameObject::Render() {
	if (!mVisible) {
		return;
	}

	AbstractImageGameObject::Render();

	if (mFramesResolution.first == 0 || mFramesResolution.second == 0) {
		return;
	}

	if (mFrameIndex >= mFramesResolution.first * mFramesResolution.second) {
		mFrameIndex = 0;
	}

	Game::GetInstance().GetSpriteRenderer()->DrawSpriteSheet(mTexture, glm::vec2(mCameraOffset.x - mScale.x / 2 * GAME_SCALE_FACTOR, mCameraOffset.y - mScale.y / 2 * GAME_SCALE_FACTOR),
															 mFrameIndex, mFramesResolution.first, mFramesResolution.second,
															 glm::vec2(mScale.x * GAME_SCALE_FACTOR, mScale.y * GAME_SCALE_FACTOR),
															 GetGlobalRotation(), mColor);
}

SpriteSheetGameObject *SpriteSheetGameObject::SetSpriteSheetFrame(int frame) {
	mFrameIndex = frame;
	return this;
}

SpriteSheetGameObject *SpriteSheetGameObject::SetSpriteSheetFrame(glm::vec2 frame) {
	mFrameIndex = frame.x * mFramesResolution.first + frame.y;
	return this;
}

SpriteSheetGameObject *SpriteSheetGameObject::AddFrameSequence(std::string name, std::vector<glm::vec2> frames) {
	mFrameSequences[name] = frames;
	return this;
}

std::vector<glm::vec2> *SpriteSheetGameObject::GetFrameSequence(std::string name) const {
	return const_cast<std::vector<glm::vec2> *>(&mFrameSequences.at(name));
}

glm::vec2 SpriteSheetGameObject::GetFrameFromSequence(std::string name) const {
	return mFrameSequences.at(name).at(mFrameIndex);
}

unsigned int SpriteSheetGameObject::GetFrameIndex() const {
	return mFrameIndex;
}
