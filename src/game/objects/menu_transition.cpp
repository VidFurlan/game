#include "menu_transition.hpp"

#include <functional>
#include <iostream>
#include <string>

#include "game.hpp"
#include "glm/common.hpp"

MenuTransition::MenuTransition(std::string name, GameObject *parent) : SpriteGameObject(name, parent, "transition") {
	SetScale({Game::GetInstance().GetWindow()->GetWidth(), Game::GetInstance().GetWindow()->GetHeight()});
	SetVisible(false);
	SetZIndex(100);
    SetVisible(false);
    mColor.a = 0.5f;
}

void MenuTransition::Update(float deltaTime) {
    
}

void MenuTransition::Transition(std::function<void()> callback) {
	SetVisible(true);
    callback();
}
