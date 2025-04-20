#include "abstract_image_game_object.hpp"

#include <algorithm>
#include <iostream>

#include "drawable_game_object.hpp"
#include "game.hpp"
#include "glm/common.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float2.hpp"
#include "resource_manager.hpp"

AbstractImageGameObject::AbstractImageGameObject(std::string name, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : DrawableGameObject(name, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, GameObject *parent, std::string textureName, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : DrawableGameObject(name, parent, pos, scale), mTexture(ResourceManager::GetInstance().GetTexture(textureName)), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : DrawableGameObject(name, pos, scale), mTexture(texture), mColor(color) {
}

AbstractImageGameObject::AbstractImageGameObject(std::string name, GameObject *parent, Texture &texture, glm::vec3 pos, glm::vec2 scale, glm::vec4 color)
    : DrawableGameObject(name, parent, pos, scale), mTexture(texture), mColor(color) {
}

AbstractImageGameObject *AbstractImageGameObject::SetColor(glm::vec4 color) {
	mColor = color;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetTexture(Texture &texture) {
	mTexture = texture;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetScale(glm::vec2 scale) {
	mScale = scale;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetScaleX(float scaleX) {
	mScale.x = scaleX;
	return this;
}

AbstractImageGameObject *AbstractImageGameObject::SetScaleY(float scaleY) {
	mScale.y = scaleY;
	return this;
}

glm::vec4 AbstractImageGameObject::GetColor() {
	return mColor;
}

Texture &AbstractImageGameObject::GetTexture() {
	return mTexture;
}

glm::vec2 AbstractImageGameObject::GetScale() const {
	return mScale;
}

float AbstractImageGameObject::GetScaleX() const {
	return mScale.x;
}

float AbstractImageGameObject::GetScaleY() const {
	return mScale.y;
}
