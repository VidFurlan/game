#pragma once

#include <string>

#include "abstract_image_game_object.hpp"
#include "drawable_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float4.hpp"
#include "imgui.h"

class TextGameObject : public DrawableGameObject {
   public:
	struct TextProperties {
		std::string fontName;
		glm::vec4 color;
		float scale;
		bool center;

		TextProperties(std::string fontName = "default", float scale = 100.0f, bool center = false, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
		    : fontName(fontName), color(color), scale(scale), center(center) {
		}
	};

	TextGameObject(std::string name, std::string text, TextProperties textProperties = TextProperties(), glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	TextGameObject(std::string name, GameObject *parent, std::string text, TextProperties textProperties = TextProperties(), glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));

	virtual void Render() override;

	TextGameObject *SetText(std::string text);
	std::string GetText() const;

	TextGameObject *SetTextProperties(TextProperties textProperties);
	TextProperties GetTextProperties() const;

   private:
	std::string mText;
	TextProperties mTextProperties;
};
