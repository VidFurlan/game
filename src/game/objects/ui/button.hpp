#pragma once

#include "abstract_image_game_object.hpp"
#include "game_object.hpp"
#include "rect_collider_game_object.hpp"

class Button : public GameObject {
   public:
	Button(std::string name, GameObject *parent, glm::vec3 position, glm::vec2 size, std::function<void()> onClick, AbstractImageGameObject *image, ScreenAnchor screenAnchor = ScreenAnchor::TOP_LEFT);
    ~Button() override;
    virtual void Update(float deltaTime) override;
    virtual void LateUpdate(float deltaTime) override;

    void RegisterClick();

   private:
	std::function<void()> mOnClick;
    bool mClicked = false;
    bool mHovered = false;
};
