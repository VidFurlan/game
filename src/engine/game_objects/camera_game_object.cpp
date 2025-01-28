#include "camera_game_object.hpp"
#include <iostream>
#include "game_object.hpp"

#include "game.hpp"

CameraGameObject::CameraGameObject(std::string name, glm::vec3 pos)
	: GameObject(name, pos) {
	Game::GetInstance().GetActiveScene()->AddGameCamera(this);
}

CameraGameObject::CameraGameObject(std::string name, GameObject *parent, glm::vec3 pos)
	: GameObject(name, parent, pos) {
	Game::GetInstance().GetActiveScene()->AddGameCamera(this);
}

CameraGameObject::~CameraGameObject() {
    Game::GetInstance().GetActiveScene()->RemoveGameCamera(this);
}

void CameraGameObject::Use() {
    Game::GetInstance().GetActiveScene()->SetActiveCamera(this);
}

CameraGameObject *CameraGameObject::SetZoom(float zoom) {
    mZoom = zoom;
    return this;
}

float CameraGameObject::GetZoom() const {
    return mZoom;
}
