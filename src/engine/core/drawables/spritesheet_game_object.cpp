#include "spritesheet_game_object.hpp"

#include <iostream>

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

	if (mFramesResolution.first == 0 || mFramesResolution.second == 0) {
		return;
	}

	if (mFrameIndex >= mFramesResolution.first * mFramesResolution.second) {
		mFrameIndex = 0;
	}

	switch (mRenderType) {
		case FIT: {
			Game::GetInstance().GetSpriteRenderer()->DrawSpriteSheet(mTexture, glm::vec2(mPos.x, mPos.y),
																	 mFrameIndex, mFramesResolution.first, mFramesResolution.second,
																	 glm::vec2(mScale.x * mTexture.Width / (float)mFramesResolution.second, mScale.y * mTexture.Height / (float)mFramesResolution.first),
																	 mPos.z, mColor);
		} break;

		case STRETCH: {
			float maxFactor = std::max(mTexture.Width / mScale.x, mTexture.Height / mScale.y);
			Game::GetInstance().GetSpriteRenderer()->DrawSpriteSheet(mTexture, glm::vec2(mPos.x, mPos.y),
																	 mFrameIndex, mFramesResolution.second, mFramesResolution.first,
																	 glm::vec2(maxFactor * mScale.x / (float)mFramesResolution.second, maxFactor * mScale.y / (float)mFramesResolution.first),
																	 mPos.z, mColor);
		} break;
	}
}

void SpriteSheetGameObject::SetSpriteSheetFrame(int frame) {
	mFrameIndex = frame;
}

void SpriteSheetGameObject::SetSpriteSheetFrame(glm::vec2 frame) {
	mFrameIndex = frame.x * mFramesResolution.first + frame.y;
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
