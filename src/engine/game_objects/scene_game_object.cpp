#include "scene_game_object.hpp"

#include <iostream>

#include "game.hpp"
#include "glm/fwd.hpp"

SceneGameObject::SceneGameObject(std::string name)
    : GameObject(name, glm::vec3(0.0f)) {
	pSpriteRenderer = Game::GetInstance().GetSpriteRenderer();
	pResourceManager = &Game::GetInstance().GetResourceManager()->GetInstance();
}

SceneGameObject *SceneGameObject::AddGameCamera(CameraGameObject *camera) {
	mCameras[camera->GetName()] = camera;
	return this;
}

SceneGameObject *SceneGameObject::RemoveGameCamera(CameraGameObject *camera) {
    if (camera == nullptr) {
        std::cerr << "Camera is nullptr" << std::endl;
        return this;
    }
    std::cout << camera << std::endl;
	mCameras.erase(camera->GetName());
	if (pActiveCamera == camera) {
		pActiveCamera = nullptr;
	}
	return this;
}

SceneGameObject *SceneGameObject::SetActiveCamera(CameraGameObject *camera) {
	pActiveCamera = camera;
	return this;
}

SceneGameObject *SceneGameObject::SetActiveCamera(std::string cameraName) {
	if (mCameras.find(cameraName) != mCameras.end()) {
		pActiveCamera = mCameras[cameraName];
	} else {
		std::cerr << "Camera " << cameraName << " not found in scene " << mName << std::endl;
	}
	return this;
}

CameraGameObject *SceneGameObject::GetActiveCamera() const {
    if (pActiveCamera == nullptr) {
        std::cerr << "No active camera set for scene " << mName << std::endl;
    }
	return pActiveCamera;
}

glm::vec3 SceneGameObject::GetBackgroundColor() const {
	return mBackgroundColor;
}

void SceneGameObject::Update(float deltaTime) {
    if (pActiveCamera == nullptr) {
        std::cerr << "No active camera set for scene " << mName << std::endl;
        if (!mCameras.empty()) {
            pActiveCamera = mCameras.begin()->second;
            std::cerr << "Setting active camera to " << pActiveCamera->GetName() << std::endl;
        }
    }
	GameObject::Update(deltaTime);
}

void SceneGameObject::Render() {
	if (!mVisible) {
		return;
	}

    if (pActiveCamera == nullptr) {
        std::cerr << "No active camera set for scene " << mName << std::endl;
        if (!mCameras.empty()) {
            pActiveCamera = mCameras.begin()->second;
            std::cerr << "Setting active camera to " << pActiveCamera->GetName() << std::endl;
        }
    }

	GameObject::Render();
}
