#include "scene_game_object.hpp"
#include <iostream>
#include "game.hpp"

SceneGameObject::SceneGameObject(std::string name)
	: GameObject(name, glm::vec3(0.0f)) {
    pSpriteRenderer = Game::GetInstance().GetSpriteRenderer();
    pResourceManager = &Game::GetInstance().GetResourceManager()->GetInstance();
}

SceneGameObject::~SceneGameObject() {
    for (auto &child : children) {
        delete child.second;
    }
}

SceneGameObject *SceneGameObject::AddGameCamera(CameraGameObject *camera) {
    mCameras[camera->GetName()] = camera;
    return this;
}

SceneGameObject *SceneGameObject::RemoveGameCamera(CameraGameObject *camera) {
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
    return pActiveCamera;
}

void SceneGameObject::Render() {
    if (!mVisible) {
        return;
    }

    if (!pActiveCamera) {
        std::cerr << "No active camera set for scene " << mName << std::endl;
        return;
    }

    GameObject::Render();
}
