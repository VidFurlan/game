#pragma once

#include "game_objects/game_object.hpp"
#include "shape2d.hpp"

class PhysicsGameObject : public GameObject {
   public:
	PhysicsGameObject(std::string name, Shape2D *shape, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
	PhysicsGameObject(std::string name, GameObject *parent, Shape2D *shape, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 scale = glm::vec2(1.0f));
    ~PhysicsGameObject();

    virtual void Update(float deltaTime) override;
	virtual void Render() override;

    bool CheckCollision(PhysicsGameObject *other);

   private:
	Shape2D *mShape;
    glm::vec3 mGlobalPosition;
};
