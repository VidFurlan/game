#include "button.hpp"

#include <functional>
#include <iostream>

// cmake-format off
#include "game.hpp"
// cmake-format on

#include "GLFW/glfw3.h"
#include "abstract_image_game_object.hpp"
#include "collider_game_object.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "rect_collider_game_object.hpp"

Button::Button(std::string name, GameObject *parent, glm::vec3 position, glm::vec2 size, std::function<void()> onClick, AbstractImageGameObject *image, ScreenAnchor screenAnchor)
    : GameObject(name, parent, position), mOnClick(onClick) {
	SetZIndex(0);
	AddChild(image);
	Game::GetInstance().AddOnPressKeyCallback(GLFW_MOUSE_BUTTON_LEFT, mName, [this]() { mClicked = true; });
	(new RectColliderGameObject("Collider", this, false, {0.0f, 0.0f, 0.0f}, size))
	    ->SetOnCollision({[this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    mHovered = type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "MouseCollider";
		    if (mClicked && type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "MouseCollider" && mOnClick && Game::GetInstance().Keys[GLFW_MOUSE_BUTTON_LEFT]) {
			    mOnClick();
		    }
	    }})
	    ->SetTag(name);
	(new RectColliderGameObject("MouseCollider", this, false, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}))
	    ->SetTag(name);
};

Button::~Button() {
	Game::GetInstance().RemoveOnPressKeyCallback(GLFW_MOUSE_BUTTON_LEFT, mName);
}

void Button::Update(float deltaTime) {
	GetChild("MouseCollider")->SetPosition(Game::GetInstance().MousePosition / GAME_SCALE_FACTOR - glm::vec2(Game::GetInstance().GetWindow()->GetWidth() / 2.0f, Game::GetInstance().GetWindow()->GetHeight() / 2.0f) / GAME_SCALE_FACTOR - glm::make_vec2(GetGlobalPosition()));
    mHovered = false;

	GameObject::Update(deltaTime);
}

void Button::LateUpdate(float deltaTime) {
	if (mHovered) {
		((AbstractImageGameObject *)GetChild("Image"))->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
	} else {
		((AbstractImageGameObject *)GetChild("Image"))->SetColor({1.0f, 1.0f, 1.0f, 0.5f});
	}
	mClicked = false;
	GameObject::LateUpdate(deltaTime);
}
