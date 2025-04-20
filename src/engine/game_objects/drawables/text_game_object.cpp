#include "text_game_object.hpp"
#include "abstract_image_game_object.hpp"
#include "drawable_game_object.hpp"
#include "game.hpp"

TextGameObject::TextGameObject(std::string name, std::string text, TextProperties textProperties, glm::vec3 pos, glm::vec2 scale)
    : DrawableGameObject(name, pos, scale), mText(text), mTextProperties(textProperties) {}

TextGameObject::TextGameObject(std::string name, GameObject *parent, std::string text, TextProperties textProperties, glm::vec3 pos, glm::vec2 scale)
    : DrawableGameObject(name, parent, pos, scale), mText(text), mTextProperties(textProperties) {}

void TextGameObject::Render() {
    if (GetVisible()) {
        DrawableGameObject::Render();
        Game::GetInstance().GetFontRenderer(mTextProperties.fontName)->DrawText(mText, mRenderPosition, mRenderSize.x * mTextProperties.scale, mTextProperties.color);
    }
}

void TextGameObject::SetText(std::string text) {
    mText = text;
}

std::string TextGameObject::GetText() const {
    return mText;
}
