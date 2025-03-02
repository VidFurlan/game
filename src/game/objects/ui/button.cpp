#include "button.hpp"

#include <algorithm>
#include <iostream>

#include "abstract_image_game_object.hpp"
#include "collider_game_object.hpp"
#include "collision_manager.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "rect_collider_game_object.hpp"

Button::Button(std::string name, GameObject *parent, glm::vec3 position, glm::vec2 size, std::function<void()> onClick, AbstractImageGameObject *image, ScreenAnchor screenAnchor)
    : GameObject(name, parent, position), mOnClick(onClick) {
	SetZIndex(0);
	AddChild(image);
	image->SetScreenAnchor(screenAnchor);
	(new RectColliderGameObject("Collider", this, false, {0.0f, 0.0f, 0.0f}, size))
	    ->SetOnCollision({[this](ColliderGameObject *other, ColliderGameObject::CollisionType type) {
		    if (type == ColliderGameObject::CollisionType::OVERLAP && other->GetName() == "MouseCollider" && mOnClick && Game::GetInstance().Keys[GLFW_MOUSE_BUTTON_LEFT]) {
			    mOnClick();
		    }
	    }})
	    ->SetTag(name);
	(new RectColliderGameObject("MouseCollider", this, false, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}))
	    ->SetTag(name);
};

void Button::Update(float deltaTime) {
	GetChild("MouseCollider")->SetPosition(Game::GetInstance().MousePosition / GAME_SCALE_FACTOR 
            - glm::vec2(Game::GetInstance().GetWindow()->GetWidth() / 2.0f, Game::GetInstance().GetWindow()->GetHeight() / 2.0f) / GAME_SCALE_FACTOR
            - glm::make_vec2(GetGlobalPosition()));

	GameObject::Update(deltaTime);
}
