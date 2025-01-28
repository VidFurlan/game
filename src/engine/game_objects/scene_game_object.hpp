#pragma once

#include <map>
#include <string>

#include "camera_game_object.hpp"
#include "game_object.hpp"
#include "glm/fwd.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

class SceneGameObject : public GameObject {
   public:
	SceneGameObject(std::string name);
	virtual ~SceneGameObject();

	virtual void Init() = 0;
    
    virtual void Render() override;

    SceneGameObject *AddGameCamera(CameraGameObject *camera);
    SceneGameObject *RemoveGameCamera(CameraGameObject *camera);
    SceneGameObject *SetActiveCamera(CameraGameObject *camera);
    SceneGameObject *SetActiveCamera(std::string cameraName);

    CameraGameObject *GetActiveCamera() const;

    glm::vec3 GetBackgroundColor() const;

   protected:
    std::map<std::string, CameraGameObject *> mCameras;
    CameraGameObject *pActiveCamera = nullptr;

	SpriteRenderer *pSpriteRenderer = nullptr;
    ResourceManager *pResourceManager = nullptr;

    glm::vec3 mBackgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);
};
